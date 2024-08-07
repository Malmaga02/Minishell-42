/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:29:13 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/26 13:43:39 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	equal_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	doppelganger_check(t_list *envp, char *all, int len)
{
	char	*key;
	char	*str;

	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (0);
	ft_strlcpy(key, all, len + 1);
	while (envp)
	{
		str = (char *)envp->content;
		if (strncmp(str, key, len) == 0
			&& (str[len] == '=' || str[len] == '+' || str[len] == '\0'))
			return (free(key), 1);
		if (len == 0 && (ft_strncmp(str, all, ft_strlen(all)) == 0))
			return (free(key), 2);
		envp = envp->next;
	}
	return (free(key), 0);
}

void	change_node_env(t_list **envp, char *str, int eq)
{
	char		*key;
	char		*value;
	t_list		*tmp;
	const int	len = ft_strlen(str) - eq + 1;

	value = malloc(sizeof(char) * len);
	ft_strlcpy(value, str + eq, len);
	key = ft_substr(str, 0, eq - 1);
	tmp = find_node_in_env(*envp, key, ft_strlen(key));
	if (!tmp)
	{
		key = strjoin_gnl(&key, value);
		ft_lstadd_back(envp, ft_lstnew(key));
		free(value);
		return ;
	}
	free(key);
	tmp->content = strjoin_gnl((char **)&tmp->content, value + 1);
	free(value);
}

int	char_check(char *str, int *error)
{
	int	i;
	int	lim;

	lim = equal_check(str);
	i = 1;
	while (str[i] && i < lim)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (export_err(str, error), 0);
		i++;
	}
	return (1);
}

void	print_export_quotes(char *str)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 12);
	while (str && str[i] != '=')
	{
		write(1, &str[i], 1);
		i++;
	}
	i++;
	write(1, "=", 1);
	write(1, "\"", 1);
	while (str && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\"", 1);
	write(1, "\n", 1);
}
