/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/06/18 14:35:00 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token_type(int token)
{
	if (token == PIPE || token == R_INPUT
	|| token == R_OUTPUT || token == D_RED_INPUT
	|| token == D_RED_OUTPUT)
		return (OPERATORS);
	else if (token == CMD || token == FILE_W || token == EOF_DEL)
		return (WORDS);
	else if (token == D_QUOTE || token == S_QUOTE)
		return (D_QUOTE);
	return (0);
}

int	count_rows_args(char **mtx_cmdline, int *arr_token)
{
	int	i;
	int	size;
	int	res;

	i = 0;
	res = 1;
	size = count_rows(mtx_cmdline);
	while (i++ < size - 1 && arr_token[i] == ARG)
		res++;
	return (res);
}

int	check_if_word_after_operator(int token)
{
	if (token == WORDS || token == D_QUOTE || token == S_QUOTE)
		return (1);
	return (0);
}