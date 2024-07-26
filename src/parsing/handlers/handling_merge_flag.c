/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_merge_flag.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:28:31 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_need_reorganize_cmdline(t_input *cmdline)
{
	t_input	*tmp;

	tmp = cmdline;
	while (tmp)
	{
		if (tmp->merge || tmp->token == DOLLAR_SIGN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	find_merge_flag_quote(char *input, int i)
{
	int	flag;

	flag = 0;
	if (i == 0)
		flag = 0;
	else if (check_cases_for_merge_with_quotes(input[i - 1], input[i]) == 1)
		flag = MERGE_PREV;
	i += handle_quotes(&input[i]);
	if (input[i] && (!char_type(input[i]) || char_type(input[i]) == D_QUOTE
			|| char_type(input[i]) == S_QUOTE))
	{
		if (flag == MERGE_PREV)
			return (MERGE_BOTH);
		return (MERGE_NEXT);
	}
	return (flag);
}

int	find_merge_flag_dollar_sign(char *input, int i)
{
	int	flag;

	flag = 0;
	if (!input || !input[i])
		return (flag);
	if (i == 0)
		flag = 0;
	else if (input[i - 1] && (!char_type(input[i - 1])
			|| char_type(input[i - 1]) == D_QUOTE
			|| char_type(input[i - 1]) == S_QUOTE))
		flag = MERGE_PREV;
	i += handle_operators(&input[i]);
	if (input[i] && (!char_type(input[i]) || char_type(input[i]) == D_QUOTE
			|| char_type(input[i]) == D_QUOTE))
	{
		if (flag == MERGE_PREV)
			return (MERGE_BOTH);
		return (MERGE_NEXT);
	}
	return (flag);
}

int	find_which_merge_flag(char *input, int i, int token)
{
	if (token == D_QUOTE || token == S_QUOTE)
		return (find_merge_flag_quote(input, i));
	else if (token == DOLLAR_SIGN)
		return (find_merge_flag_dollar_sign(input, i));
	return (0);
}
