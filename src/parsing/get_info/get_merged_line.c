/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_merged_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:28:31 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content_merged(char **mtx, int *i, int *merge_arr, int size)
{
	int		index;
	char	*quote;
	char	*content;

	index = *i;
	quote = NULL;
	content = NULL;
	while (mtx && mtx[*i])
	{
		quote = ft_strdup("\"");
		mtx[*i + 1] = delete_empty_env(mtx[*i + 1]);
		if (*i == index)
			content = strjoin_gnl(&quote, mtx[*i]);
		if (mtx[*i + 1] && (*i < size && merge_arr[*i] == MERGE_NEXT))
			content = strjoin_gnl(&content, mtx[*i + 1]);
		if (*i + 1 < size && merge_arr[*i + 1] == STAY)
		{
			content = strjoin_gnl(&content, "\"");
			break ;
		}
		(*i)++;
	}
	if (quote)
		free(quote);
	return (content);
}

char	*handle_merge_next(char	**mtx_cmdline, int *merge_arr, int *index)
{
	int		size;
	char	*content;

	size = count_rows(mtx_cmdline);
	if (mtx_cmdline && mtx_cmdline[*index])
		mtx_cmdline[*index] = delete_empty_env(mtx_cmdline[*index]);
	content = get_content_merged(mtx_cmdline, index, merge_arr, size);
	index = find_index(*index, merge_arr, size);
	return (content);
}

char	*get_new_input(char	**mtx_cmdline, int *merge_arr, int size)
{
	int		i;
	char	*content;
	char	*new_input;

	i = 0;
	content = NULL;
	new_input = NULL;
	while ((mtx_cmdline && mtx_cmdline[i]) && i < size)
	{
		new_input = strjoin_gnl(&new_input, " ");
		content = NULL;
		if (i < size && merge_arr[i] == STAY)
			content = strjoin_gnl(&content, mtx_cmdline[i]);
		if (i < size && merge_arr[i] == MERGE_NEXT)
		{
			content = handle_merge_next(mtx_cmdline, merge_arr, &i);
			i += count_merge_next(merge_arr, i, size);
		}
		if (!content || !content[0])
			return (NULL);
		new_input = strjoin_gnl(&new_input, content);
		free(content);
		i++;
	}
	return (new_input);
}

char	*get_merged_line(t_input *cmd_line, int *merge_arr)
{
	char	*new_input;
	char	**mtx_cmdline;
	int		size;

	new_input = NULL;
	size = dll_input_size(cmd_line);
	mtx_cmdline = parsing_list_in_mtx(cmd_line);
	if (!merge_arr || !mtx_cmdline)
		return (NULL);
	merge_arr = get_merge_arr(cmd_line, merge_arr, size);
	merge_arr = organize_merge_arr(merge_arr, size);
	new_input = get_new_input(mtx_cmdline, merge_arr, size);
	free(merge_arr);
	free_mtx(mtx_cmdline);
	return (new_input);
}
