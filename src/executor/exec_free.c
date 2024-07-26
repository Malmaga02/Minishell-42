/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:59:23 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/26 14:55:39 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_all *shell)
{
	int	i;

	i = 0;
	while (shell->pipes && shell->pipes[i])
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	free_pipes(t_all *shell)
{
	int	i;

	i = 0;
	if (!shell->pipes)
		return ;
	while (shell->pipes[i])
	{
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	shell->pipes = NULL;
}

void	free_heredoc(t_all *shell)
{
	t_input	*current;

	current = shell->cmd_line;
	while (current)
	{
		if (current->heredoc_file != NULL)
		{
			unlink(current->heredoc_file);
			free(current->heredoc_file);
			current->heredoc_file = NULL;
		}
		current = current->next;
	}
}
