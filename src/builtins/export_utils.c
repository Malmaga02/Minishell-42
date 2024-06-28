/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:29:13 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/28 17:37:37 by lotrapan         ###   ########.fr       */
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

void	change_node_env(t_list **envp, char *str, int eq)
{
	if (doppelganger_check(*envp, str, eq - 1))
	{
		(*envp)->content;

	}
	ft_strlcpy(key, str, eq - 1);
	if (envp)
		printf("%s\n", key);
}
