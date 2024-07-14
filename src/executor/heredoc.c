/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/10 17:06:43 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_heredoc(char *delimiter, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || strcmp(line, delimiter) == 0)
			return (free(line));
		*fd = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
			return (ft_printf(2, "heredoc denied\n"), free(line));
		ft_putendl_fd(line, *fd);
		free(line);
	}
}

int	open_heredoc(t_input *block)
{
	char		*line;
	t_input		*cmd;
	int			fd;

	fd = -1;
	cmd = find_cmd_in_block(block);
	line = NULL;
	while (block && block->token != PIPE)
	{
		if (block->token == D_RED_INPUT)
			display_heredoc(block->args[1], &fd);
		block = block->next;
	}
	if (cmd && fd != -1)
		fd = cmd->fd_in;
	return (1);
}

int	handle_heredoc(t_all *shell)
{
	t_input	*current;

	current = shell->cmd_line;
	open_heredoc(current);
	while (current)
	{
		if (current->token == PIPE)
			open_heredoc(current->next);
		current = current->next;
	}
	return (1);
}
