/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:59:23 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/10 16:16:55 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_all *shell)
{
	int i;

	i = 0;
	while (shell->pipes && shell->pipes[i])
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void free_pipes(t_all *shell)
{
	int i;

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
