/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arr_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:28 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*handle_redirect_word_token(int *arr_token, int size)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	while (i < size)
	{
		if (arr_token[i] == CMD)
			cmd = 1;
		if (check_which_operator(arr_token[i]) == REDIRECTS && cmd == 0)
		{
			i++;
			if (i + 1 < size
				&& ((arr_token[i] == FILE_W || arr_token[i] == EOF_DEL)
					&& find_token_type(arr_token[i + 1]) == WORDS))
				arr_token[++i] = CMD;
			cmd = 0;
		}
		i++;
	}
	return (arr_token);
}

int	handle_exp_with_heredoc(int *arr_token, int index, int token)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (arr_token[i] == HEREDOC)
			return (EOF_DEL);
		i++;
	}
	return (token);
}

int	first_token_check(int *arr_token, int size)
{
	int	i;

	i = 0;
	if (!arr_token)
		return (0);
	if (arr_token[0] == PIPE
		|| find_token_type(arr_token[size - 1]) == OPERATORS)
		return (ft_putstr_fd(SYNTAX_ERROR, 0), 0);
	while (i < size && arr_token[i])
	{
		while (i < size && arr_token[i] == WORDS)
			i++;
		if (i < size && (find_token_type(arr_token[i]) == OPERATORS
				&& !handle_syntax_error_operators(arr_token, i, size)))
			return (0);
		i++;
	}
	return (1);
}

int	*analyse_words_token(int *arr_token, int size)
{
	int	i;

	i = 0;
	if (!arr_token)
		return (0);
	while (i < size && arr_token[i])
	{
		if (i == 0 && arr_token[i] == WORDS)
			arr_token[i] = get_word_token(0);
		if ((i != 0 && i < size) && arr_token[i] == WORDS)
			arr_token[i] = get_word_token(arr_token[i - 1]);
		if (i < size && (arr_token[i] == DOLLAR_SIGN
				|| arr_token[i] == D_QUOTE))
			arr_token[i] = handle_exp_with_heredoc(arr_token, i, arr_token[i]);
		i++;
	}
	arr_token = handle_redirect_word_token(arr_token, size);
	return (arr_token);
}

int	*get_arr_token(char **mtx, int size)
{
	int	i;
	int	*arr_token;

	i = 0;
	arr_token = ft_calloc(size, sizeof(int));
	if (!arr_token)
		return (NULL);
	while (mtx && mtx[i])
	{
		arr_token[i] = find_token(mtx[i]);
		i++;
	}
	if (!first_token_check(arr_token, size))
		return (NULL);
	arr_token = analyse_words_token(arr_token, size);
	return (arr_token);
}
