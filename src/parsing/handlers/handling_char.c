/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:28:31 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_type(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\"')
		return (D_QUOTE);
	else if (c == '\'')
		return (S_QUOTE);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (R_INPUT);
	else if (c == '>')
		return (R_OUTPUT);
	else if (c == '$')
		return (DOLLAR_SIGN);
	return (0);
}

int	handle_quotes(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	if (char_type(s[i]) == D_QUOTE)
	{
		if (s[++i] && char_type(s[i]) == D_QUOTE)
			return (++i);
		while ((s && s[i]) && char_type(s[i]) != D_QUOTE)
			i++;
	}
	else if (char_type(s[i]) == S_QUOTE)
	{
		if (s[++i] && char_type(s[i]) == S_QUOTE)
			return (++i);
		while ((s && s[i]) && char_type(s[i]) != S_QUOTE)
			i++;
	}
	if (!s[i])
		return (-1);
	return (++i);
}

int	handle_dollar_signs(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (char_type(s[i]) == 1 || char_type(s[i]) == DOLLAR_SIGN
			|| char_type(s[i]) == D_QUOTE || char_type(s[i]) == S_QUOTE)
			return (i);
		i++;
	}
	return (i);
}

int	handle_operators(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	if (s[i] && char_type(s[i]) == PIPE)
		return (++i);
	else if (s[i] && char_type(s[i]) == R_INPUT)
	{
		if (s[i + 1] && char_type(s[i + 1]) == R_INPUT)
			return (2);
		return (++i);
	}
	else if (s[i] && char_type(s[i]) == R_OUTPUT)
	{
		if (s[i + 1] && char_type(s[i + 1]) == R_OUTPUT)
			return (2);
		return (++i);
	}
	else if (s[i] && char_type(s[i++]) == DOLLAR_SIGN)
	{
		i += handle_dollar_signs(&s[i]);
	}
	return (i);
}

int	handle_not_spaces(char *s)
{
	int	i;
	int	tmp;

	tmp = 0;
	i = 0;
	if (!s || !s[i])
		return (0);
	if (s[i] && find_token_type(char_type(s[i])) == QUOTES)
		tmp = handle_quotes(&s[i]);
	if (s[i] && (find_token_type(char_type(s[i])) == OPERATORS
			|| find_token_type(char_type(s[i])) == DOLLAR_SIGN))
		tmp = handle_operators(&s[i]);
	while (s[i] && !char_type(s[i]))
		i++;
	if (tmp == -1)
		return (-1);
	i += tmp;
	return (i);
}
