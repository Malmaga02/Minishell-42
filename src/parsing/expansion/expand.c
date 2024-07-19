/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/16 19:03:19 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*expand_env(char *content, t_all all_info)
{
	char	*env;
	char	*new_content;

	env = get_env(content, all_info);
	if (!env || !content)
		return (free(content), NULL);
	new_content = ft_strdup(env);
	if (!new_content)
		return (free(content), NULL);
	if (len_escaped_char(new_content) == (int)ft_strlen(new_content))
		return (free(env), free(content), (void *)new_content);
	new_content = handle_escaped_char(new_content);
	if (!new_content)
		return (free(content), NULL);
	free(env);
	free(content);
	return ((void *)new_content);
}

void	*expand_env_with_quotes(char *content, t_all all_info)
{
	char	*env;
	char	*new_content;
	int		dollar_signs;

	dollar_signs = check_dollar_sign(content);
	while (dollar_signs > 0)
	{
		env = get_env(content, all_info);
		content = get_content_with_quotes(content, env);
		if (!env || !content)
			return (NULL);
		dollar_signs--;
		free(env);
	}
	new_content = ft_strdup(content);
	free(content);
	return ((void *)new_content);
}

t_all	expand_dollar_sign(t_all all_info)
{
	t_input	*tmp;

	tmp = all_info.cmd_line;
	while (tmp)
	{
		if (tmp->token == D_QUOTE && check_dollar_sign(tmp->content))
			tmp->content = expand_env_with_quotes(tmp->content, all_info);
		else if (tmp->token == DOLLAR_SIGN)
			tmp->content = expand_env(tmp->content, all_info);
		if (!tmp->content)
			return ((t_all){0});
		tmp = tmp->next;
	}
	return (all_info);
}
