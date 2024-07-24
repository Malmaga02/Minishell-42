/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/24 19:06:34 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finish_heredoc(char *file_name, int fd, int *last)
{
	int	new;

	if (fd > 0)
		close(fd);
	new = open(file_name, O_RDONLY);
	if (last != NULL)
		*last = new;
}

static int	display_heredoc(char *delimiter, int *last, t_all *shell, int *fd)
{
	char	*line;

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
			return (0);
		heredoc_putendl_fd(line, *fd, shell);
	}
	return (1);
}

void	set_heredoc(t_input *block, t_input *cmd, int *last)
{
	t_input	*tmp;

	tmp = block->prev;
	while (tmp || tmp->token == PIPE)
	{
		if (tmp->token == HEREDOC)
		{
			last = &cmd->fd_in;
		}
		else if (tmp->token == R_INPUT)
		{
			unlink(cmd->heredoc_file);
			free(cmd->heredoc_file);
			last = NULL;
		}
	}
	
}

static int	open_heredoc(t_input *block, t_all *shell)
{
	t_input	*cmd;
	int		*last;
	int		fd;
	char	*file_name;

	last = NULL;
	cmd = find_cmd_in_block(block);
	if (cmd)
		cmd->heredoc_file = open_file("heredoc", &fd);
	else
		file_name = open_file("heredoc", &fd);
	while (block && block->token != PIPE)
	{
		if (block->token == HEREDOC)
		{
			if (!display_heredoc(block->args[1], last, shell, &fd))
				return (0);
		}
		block = block->next;
	}
	finish_heredoc(file_name, fd, last);
	if (!cmd)
	{
		unlink(file_name);
		free(file_name);
		return (1);
	}
	set_heredoc(block, cmd, last);
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
