/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_merge_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:28:17 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:28:31 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cases_for_merge_with_quotes(char current, char before)
{
	if (!current || !before)
		return (-1);
	if (!char_type(before)
		|| (char_type(current) == D_QUOTE && char_type(before) == S_QUOTE)
		|| (char_type(current) == S_QUOTE && char_type(before) == D_QUOTE))
		return (1);
	return (0);
}

t_input	*switch_merge_flag(t_input *cmd_line, int token_nbr, int which_merge)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = cmd_line;
	while (tmp)
	{
		if (tmp->token == D_QUOTE || tmp->token == S_QUOTE
			|| tmp->token == DOLLAR_SIGN)
		{
			if (i == token_nbr)
				tmp->merge = which_merge;
			i++;
		}
		tmp = tmp->next;
	}
	return (cmd_line);
}

t_input	*handle_merge_flag(char *input, t_input *cmd_line, int token_nbr, int i)
{
	int		token;
	int		which_flag;

	token = char_type(input[i]);
	which_flag = find_which_merge_flag(input, i, token);
	cmd_line = switch_merge_flag(cmd_line, token_nbr, which_flag);
	return (cmd_line);
}

t_input	*check_if_need_merge(t_parsing *parsing, t_input *cmd_line)
{
	char	*input;
	int		i;
	int		token_nbr;

	i = 0;
	token_nbr = 0;
	input = parsing->input;
	while (input && input[i])
	{
		if (char_type(input[i]) == D_QUOTE || char_type(input[i]) == S_QUOTE
			|| char_type(input[i]) == DOLLAR_SIGN)
		{
			cmd_line = handle_merge_flag(input, cmd_line, token_nbr, i);
			token_nbr++;
			if (char_type(input[i]) == D_QUOTE
				|| char_type(input[i]) == S_QUOTE)
				i += handle_quotes(&input[i]) - 1;
			else if (char_type(input[i]) == DOLLAR_SIGN)
				i += handle_operators(&input[i]) - 1;
		}
		i++;
	}
	return (cmd_line);
}
