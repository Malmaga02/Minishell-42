/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/16 19:03:19 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_len_env(t_list *envp, char *name_env)
{
	t_list	*tmp;
	char	*content;
	int		len;
	int		lst_size;

	tmp = envp;
	content = NULL;
	len = ft_strlen(name_env);
	lst_size = ft_lstsize(envp);
	while (tmp && lst_size > 0)
	{
		content = (char *)tmp->content;
		if (lst_size > 0 && !ft_strncmp(content, name_env, len))
			return (ft_strlen(content) - len);
		tmp = tmp->next;
		lst_size--;
	}
	return (-1);
}

char	*find_expansion_env(t_list *envp, char *name_env)
{
	t_list	*tmp;
	char	*content;
	int		len;

	tmp = envp;
	content = NULL;
	len = ft_strlen(name_env);
	while (tmp)
	{
		content = (char *)tmp->content;
		if (!ft_strncmp(content, name_env, len))
			return (&content[len]);
		tmp = tmp->next;
	}
	return (NULL);
}

int	len_escaped_char(char *env)
{
	int		i;
	int		res;
	int		token;

	i = 0;
	res = 0;
	token = 0;
	while (env && env[i])
	{
		token = check_spaces(env[i]);
		if (find_token_type(token) == OPERATORS
			|| find_token_type(token) == QUOTES)
			res++;
		i++;
	}
	return (i + res);
}

char	*handle_escaped_char(char *env)
{
	int		i;
	int		j;
	int		token;
	char	*new_content;

	i = 0;
	j = 0;
	token = 0;
	new_content = ft_calloc(len_escaped_char(env) + 1, sizeof(char));
	if (!new_content)
		return (NULL);
	while (env && env[i])
	{
		token = check_spaces(env[i]);
		if (find_token_type(token) == OPERATORS
			|| find_token_type(token) == QUOTES)
			new_content[j++] = '$';
		new_content[j++] = env[i++];
	}
	return (free(env), new_content);
}
