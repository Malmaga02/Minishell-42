/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/16 19:03:19 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (token == R_INPUT || token == R_OUTPUT || token == D_RED_OUTPUT)
		return (REDIRECTS);
	if (token == D_QUOTE || token == S_QUOTE)
		return (QUOTES);
	if (token == HEREDOC)
		return (HEREDOC);
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
				return (ft_putstr_fd("syntax error near unexpected token\n", 2), 0);
			return (1);
		}
		tkn_before = arr_token[i - 1];
		if ((arr_token[i] == PIPE && find_token_type(tkn_before) == OPERATORS)
			|| (check_which_operator(arr_token[i]) == REDIRECTS
				&& find_token_type(tkn_after) == OPERATORS))
			return (ft_putstr_fd("syntax error near unexpected token\n", 2), 0);
	}
	return (1);
}
