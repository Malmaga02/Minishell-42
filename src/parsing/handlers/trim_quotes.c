/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/16 19:03:19 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *content)
{
	char	*new_content;
	char	*to_trim;

	to_trim = ft_calloc(2, sizeof(char));
	if (!to_trim)
		return (NULL);
	to_trim[0] = content[0];
	new_content = ft_strtrim(content, to_trim);
	free(to_trim);
	return (new_content);
}

char	*trim_dollar_signs(char *content)
{
	char	*new_content;
	char	*to_trim;

	to_trim = ft_calloc(2, sizeof(char));
	if (!to_trim)
		return (NULL);
	to_trim[0] = '$';
	new_content = ft_strtrim(content, to_trim);
	free(to_trim);
	return (new_content);
}

char	*trim(char *content, int token)
{
	char	*new_content;

	new_content = NULL;
	if (token == QUOTES)
		new_content = trim_quotes(content);
	else if (token == DOLLAR_SIGN)
		new_content = trim_dollar_signs(content);
	free(content);
	return (new_content);
}

t_all	handle_trim_special_char(t_all all_info, int token)
{
	t_input	*tmp;

	if (!all_info.cmd_line)
		return ((t_all){0});
	tmp = all_info.cmd_line;
	while (tmp)
	{
		if (find_token_type(tmp->token) == token)
			tmp->content = trim(tmp->content, token);
		if (!tmp->content)
			return (set_clear_all(&all_info), (t_all){0});
		tmp = tmp->next;
	}
	all_info = assign_token_as_words_token(all_info, token);
	return (all_info);
}
