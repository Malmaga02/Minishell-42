/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:51:31 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/04 21:26:59 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_all *shell, char *cmd)
{
	char	*path;
	char	*part_path;
	char	*path_env;
	int		i;
	char	**possible_paths;

	i = 0;
	path_env = find_word_in_env(shell->envp, "PATH");
	if (!path_env)
		return (NULL);
	possible_paths = ft_split(path_env, ':'); 
	if (!possible_paths)
		return (NULL);
	while (possible_paths[i])
	{
		part_path = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0) // contolla se esiste e se e' eseguibile 
			return (path);
		free(path);
		i++;
	}
	free_mtx(possible_paths);
	return (NULL);
}

char	**lst_to_mtx(t_list *envp)
{
	int		i;
	int		len;
	char	**mtx;
    t_list *tmp = NULL;

	i = 0;
	tmp = envp;
	len = ft_lstsize(tmp);
	mtx = malloc(sizeof(char *) * (len + 1));
	if (!mtx)
		return (NULL);
	while (tmp)
	{
		mtx[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	mtx[i] = NULL;
	return(mtx);
}

void	print_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx && mtx[i])
	{
		printf("%s\n", mtx[i]);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1 && s2) && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
