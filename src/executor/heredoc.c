/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/16 11:32:06 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strjoin_heredoc(char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *)malloc(len_s1 + len_s2 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len_s1 + 1);
	ft_strlcat(result, s2, len_s1 + len_s2 + 1);
	return (result);
}

static char *open_file(char *file_name, int *fd)
{
	char	*new;

	new = NULL;
	*fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
	{
		new = strjoin_heredoc(file_name, "_daje");
		return (open_file(new, fd));
	}
	return (file_name);
}

void	display_heredoc(char *delimiter, int *last)
{
	char	*line;
	char	*file_name;
	int		fd;

	file_name = open_file("heredoc", &fd);
	while (g_status_code != 130)
	{
		line = readline("> ");
		if (line == NULL || strcmp(line, delimiter) == 0)
		{
			if (line == NULL)
				ft_printf(2, "minishello: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (last != NULL)
		*last = fd;
	unlink(file_name);
}

int	open_heredoc(t_input *block)
{
	t_input		*cmd;
	int			*last;

	last = NULL;
	cmd = find_cmd_in_block(block);
	if (cmd)
		last = &cmd->fd_in;
	while (block && block->token != PIPE)
	{
		if (block->token == D_RED_INPUT)
			display_heredoc(block->args[1], last);
		block = block->next;
	}
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
