/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/19 16:43:20 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_putendl_fd(char *s, int fd, t_all *shell)
{
	if (!s || fd < 0)
		return ;
	s = expand_env_with_quotes(s, *shell);
	if (!s || g_status_code == 130)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	free(s);
}

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

static char	*open_file(char *file_name, int *fd)
{
	char	*new;

	new = NULL;
	*fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
	{
		new = strjoin_heredoc(file_name, "_daje");
		return (unlink(file_name), open_file(new, fd));
	}
	return (file_name);
}

static int	display_heredoc(char *delimiter, int *last, t_all *shell)
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
			return (unlink(file_name), 0);
		heredoc_putendl_fd(line, fd, shell);
	}
	if (fd > 0)
		close(fd);
	fd = open(file_name, O_RDONLY);
	if (last != NULL)
		*last = fd;
	unlink(file_name);
	return (1);
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
		{
			if (!display_heredoc(block->args[1], last, shell))
				return (0);
		}
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
