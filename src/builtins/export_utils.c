/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:29:13 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/01 18:04:09 by lotrapan         ###   ########.fr       */
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

int	doppelganger_check(t_list *envp, char *key, int len)
{
	char	*str;

	str = NULL;
	while (envp)
	{
		str = (char *)envp->content;
		if ((ft_strncmp(str, key, len) == 0) && ((str[len] == '=') || (str[len] == '+')))
			return (1);
		envp = envp->next;
	}	
	return (0);
}

t_list	*find_node_in_env(t_list *envp, char *word, int len)
{
	char *str;

	while (envp)
	{
		str = (char *)envp->content;
		if (ft_strncmp(str, word, len) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	change_node_env(t_list **envp, char *str, int eq)
{
	char	*key;
	char	*value;
	t_list	*tmp;
	const int	len = ft_strlen(str) - eq + 1;

	value = malloc(sizeof(char) * len);
	ft_strlcpy(value, str + eq, len);
	key = malloc(sizeof(char) * eq);
	ft_strlcpy(key, str, eq);
	tmp = find_node_in_env(*envp, key, ft_strlen(key));
	if (!tmp)
	{
		key = strjoin_gnl(&key, value);
		ft_lstadd_back(envp, ft_lstnew(key));
		printf("PORCOFFFF\n");
		return ;
	}
	tmp->content = strjoin_gnl((char **)&tmp->content, value + 1);
}

