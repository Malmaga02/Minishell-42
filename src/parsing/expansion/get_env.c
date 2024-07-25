/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:28 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_word(char *str, int index)
{
	int	len;

	len = 0;
	if (index < 0)
		return (-1);
	if (!str || !str[index])
		return (0);
	while ((str && str[index]) && !char_type(str[index++]))
		len++;
	return (len);
}

int	get_index_special_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (-1);
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_expansion(t_list *envp, char *name_env)
{
	char	*env;
	char	*tmp_env;

	if (!name_env)
		return (NULL);
	if (!ft_strncmp(name_env, "?=", 2))
		return (ft_itoa(g_status_code));
	tmp_env = find_expansion_env(envp, name_env);
	if (!tmp_env)
		return (ft_strdup(""));
	env = ft_strdup(tmp_env);
	return (env);
}

char	*get_name_env(char *str)
{
	int		i;
	int		index_dollar_sign;
	int		len_env;
	char	*name_env;

	i = 0;
	index_dollar_sign = get_index_special_char(str, '$') + 1;
	if (index_dollar_sign == -1)
		return (NULL);
	len_env = get_len_word(str, index_dollar_sign) + 1;
	name_env = ft_calloc(len_env + 1, sizeof(char));
	if (!name_env)
		return (NULL);
	while ((str && str[index_dollar_sign]) && i < len_env - 1)
	{
		name_env[i] = str[index_dollar_sign];
		index_dollar_sign++;
		i++;
	}
	name_env[i] = '=';
	return (name_env);
}

char	*get_env(char *str, t_all all_info)
{
	char	*env;
	char	*name_env;

	name_env = get_name_env(str);
	if (!name_env)
		return (NULL);
	env = get_expansion(all_info.envp, name_env);
	if (!env)
		return (NULL);
	free(name_env);
	return (env);
}

//usare semplicemente strchr? o meno efficace?
