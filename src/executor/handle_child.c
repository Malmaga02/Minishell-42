/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:55:40 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/24 15:40:44 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_fd_info(t_all *all)
{
    printf("Standard file descriptor in: %d\n", all->std_fd_in);
    printf("Standard file descriptor out: %d\n", all->std_fd_out);
    
    t_input *current_input = all->cmd_line;
    int command_index = 0;
    
    while (current_input != NULL)
    {
        printf("Command %d:\n", command_index);
        printf("  File descriptor in: %d\n", current_input->fd_in);
        printf("  File descriptor out: %d\n", current_input->fd_out);
        current_input = current_input->next;
        command_index++;
    }

    if (all->pipes)
    {
        printf("Pipes:\n");
        for (int i = 0; all->pipes[i] != NULL; i++)
        {
            printf("  Pipe %d: [%d, %d]\n", i, all->pipes[i][0], all->pipes[i][1]);
        }
    }
}

void	pipe_init(t_all *shell, t_input *current, int i)
{
	const int	num_pipes = count_pipe(shell->cmd_line);

	if (i > 0 && shell->pipes)
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	if (i < num_pipes && shell->pipes)
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
	// print_fd_info(shell);
	close_pipes(shell);
}

void	child_exe(t_all *shell, t_input *current)
{
	if (is_builtin(current))
	{
		exec_builtin(shell, current);
		/* if (shell && shell->std_fd_in > 2)
			close(shell->std_fd_in);
		if (shell && shell->std_fd_out > 2)
			close(shell->std_fd_out); */
		free_all(shell);
		close_exec_fd();
		exit(g_status_code);
	}
	else
		exec_command(shell, current);
}

void	handle_child(t_all *shell, t_input *cmd, int i)
{
	pipe_init(shell, cmd, i);
	child_exe(shell, cmd);
}
