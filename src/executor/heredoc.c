/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/20 18:15:43 by lotrapan         ###   ########.fr       */
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
	unlink(file_name);
}

static void	display_heredoc(char *delimiter, int *last, t_all *shell)
{
	char	*line;
	char	*file_name;
	int		fd;

	file_name = open_file("heredoc", &fd);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || strcmp(line, delimiter) == 0)
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
			break ;
		heredoc_putendl_fd(line, fd, shell);
	}
	finish_heredoc(file_name, fd, last);
}

static int	open_heredoc(t_input *block, t_all *shell)
{
	t_input	*cmd;
	int		*last;

	last = NULL;
	cmd = find_cmd_in_block(block);
	if (cmd)
		last = &cmd->fd_in;
	while (block && block->token != PIPE)
	{
		if (block->token == HEREDOC)
			display_heredoc(block->args[1], last, shell);
		block = block->next;
	}
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
