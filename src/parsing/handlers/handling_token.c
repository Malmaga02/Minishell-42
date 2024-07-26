/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:28:31 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_word_token(int token)
{
	if (!token || token == PIPE)
		return (CMD);
	else if (token == R_INPUT || token == R_OUTPUT
		|| token == D_RED_OUTPUT)
		return (FILE_W);
	else if (token == HEREDOC)
		return (EOF_DEL);
	else
		return (ARG);
	return (-1);
}

int	find_token(char *str)
{
	if (*str == '\"')
		return (D_QUOTE);
	else if (*str == '\'')
		return (S_QUOTE);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '<' && ft_strlen(str) == 1)
		return (R_INPUT);
	else if (*str == '>' && ft_strlen(str) == 1)
		return (R_OUTPUT);
	else if (*str == '<' && (*str++) == '<')
		return (HEREDOC);
	else if (*str == '>' && (*str++) == '>')
		return (D_RED_OUTPUT);
	else if (*str == '$')
		return (DOLLAR_SIGN);
	return (WORDS);
}

int	find_token_type(int token)
{
	if (token == PIPE || token == R_INPUT
		|| token == R_OUTPUT || token == HEREDOC
		|| token == D_RED_OUTPUT)
		return (OPERATORS);
	else if (token == CMD || token == FILE_W || token == EOF_DEL
		|| token == ARG)
		return (WORDS);
	else if (token == D_QUOTE || token == S_QUOTE)
		return (QUOTES);
	else if (token == DOLLAR_SIGN)
		return (DOLLAR_SIGN);
	return (0);
}

int	check_which_operator(int token)
{
	if (token == R_INPUT || token == R_OUTPUT || token == D_RED_OUTPUT
		|| token == HEREDOC)
		return (REDIRECTS);
	if (token == D_QUOTE || token == S_QUOTE)
		return (QUOTES);
	else
		return (token);
	return (0);
}

int	handle_syntax_error_operators(int *arr_token, int i, int size)
{
	int	tkn_before;
	int	tkn_after;

	tkn_before = 0;
	tkn_after = 0;
	if (i >= size)
		return (0);
	if (i >= 0 && (i + 1) < size)
	{
		tkn_after = arr_token[i + 1];
		if (i == 0)
		{
			if (check_which_operator(arr_token[i]) == REDIRECTS
				&& find_token_type(tkn_after) == OPERATORS)
				return (ft_putstr_fd(SYNTAX_ERROR, 2), 0);
			return (1);
		}
		tkn_before = arr_token[i - 1];
		if ((arr_token[i] == PIPE && find_token_type(tkn_before) == OPERATORS)
			|| (check_which_operator(arr_token[i]) == REDIRECTS
				&& find_token_type(tkn_after) == OPERATORS))
			return (ft_putstr_fd(SYNTAX_ERROR, 2), 0);
	}
	return (1);
}
