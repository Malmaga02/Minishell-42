/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/25 17:51:53 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finish_heredoc(char *file_name, int fd, int *last)
{
	if (fd > 0)
		close(fd);
	fd = open(file_name, O_RDONLY);
	if (last != NULL)
		*last = fd;
}

static int	display_heredoc(char *delimiter, t_all *shell, int *fd) //se delimiter non esiste
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
		{
			if (line == NULL)
			{
				ft_printf(2, "minishello: warning: here-document delimited");
				ft_printf(2, "by end-of-file (wanted `%s')\n", delimiter);
			}
			free(line);
			break ;
		}
		if (g_status_code == 130)
			return (0);
		heredoc_putendl_fd(line, *fd, shell);
	}
	return (1);
}

static int	open_heredoc(t_input *block, t_all *shell)
{
	t_input	*cmd;
	int		*last;
	int		fd;
	t_input	*node_h;

	last = NULL;
	node_h = NULL;
	fd = -1;
	cmd = find_cmd_in_block(block);
	if (cmd)
		last = &cmd->fd_in;
	while (block && block->token != PIPE)
	{
		if (block->token == HEREDOC)
		{
			node_h = block;
			block->heredoc_file = open_file("heredoc", &fd);
			if (!display_heredoc(block->args[1], shell, &fd))
				return (0);
		}
		block = block->next;
	}
	if (node_h)
		finish_heredoc(node_h->heredoc_file, fd, last);
	return (1);
}

int	handle_heredoc(t_all *shell)
{
	t_input	*current;

	current = shell->cmd_line;
	open_heredoc(current, shell);
	while (current)
	{
		if (current->token == PIPE)
			open_heredoc(current->next, shell);
		current = current->next;
	}
	return (1);
}
