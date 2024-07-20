/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:55:40 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/20 18:06:50 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_init(t_all *shell, t_input *current, int i, int num_pipes)
{
	if (i > 0 && shell->pipes)
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	if (num_pipes > 0 && shell->pipes)
		dup2(shell->pipes[i][1], STDOUT_FILENO);
	if (current->fd_in > 2)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
	}
	if (current->fd_out > 2)
	{
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
	}
	close_pipes(shell);
}

void	child_exe(t_all *shell, t_input *current)
{
	if (is_builtin(shell))
	{
		exec_builtin(shell);
		if (shell && shell->std_fd_in > 2)
			close(shell->std_fd_in);
		if (shell && shell->std_fd_out > 2)
			close(shell->std_fd_out);
		free_pipes(shell);
		free_all(shell);
		close_exec_fd();
		exit(g_status_code);
	}
	else
		exec_command(shell, current);
}

void	handle_child(t_all *shell, t_input *cmd, int i, int num_pipes)
{
	pipe_init(shell, cmd, i, num_pipes);
	child_exe(shell, cmd);
}
