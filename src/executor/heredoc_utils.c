/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:07:47 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/24 14:36:26 by lotrapan         ###   ########.fr       */
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

char	*open_file(char *file_name, int *fd)
{
	char	*new;

	new = NULL;
	*fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (*fd < 0)
	{
		new = strjoin_heredoc(file_name, "_daje");
		if (!new)
			return (NULL);
		return (open_file(new, fd));
	}
	return (file_name);
}

void	heredoc_putendl_fd(char *s, int fd, t_all *shell)
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
