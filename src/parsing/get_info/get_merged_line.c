/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_merged_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/16 11:25:01 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_merge_arr(t_input *cmd_line, int *merge_arr, int size)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = cmd_line;
	while (tmp && i < size)
	{
		merge_arr[i] = tmp->merge;
		i++;
		tmp = tmp->next;
	}
	return (merge_arr);
}

int	*organize_merge_arr(int *merge_arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((merge_arr[i] == MERGE_PREV || merge_arr[i] == MERGE_BOTH) && i != 0)
		{
			merge_arr[i - 1] = MERGE_NEXT;
			if (merge_arr[i] == MERGE_PREV)
				merge_arr[i] = STAY;
			else if (merge_arr[i] == MERGE_BOTH)
				merge_arr[i] = MERGE_NEXT;
		}
		i++;
	}
	return (merge_arr);
}

int	count_merge_next(int *merge_arr, int i, int size)
{
	int	res;

	res = 1;
	while (i < size && merge_arr[i++] == MERGE_NEXT)
		res++;
	return (res - 1);	
}

char	*handle_merge_next(char	**mtx_cmdline, int *merge_arr, int *index)
{
	int		i;
	int		size;
	char	*content;
	char	*quote;

	i = *index;
	size = count_rows(mtx_cmdline); 
	content = NULL;
	quote = NULL;
	while (mtx_cmdline && mtx_cmdline[i])
	{
		quote = ft_strdup("\"");
		if (i == *index)
			content = strjoin_gnl(&quote, mtx_cmdline[i]);
		if (mtx_cmdline[i + 1] && (i < size && merge_arr[i] == MERGE_NEXT))
			content = strjoin_gnl(&content, mtx_cmdline[i + 1]);
		if (i + 1 < size && merge_arr[i + 1] == STAY)
		{
			content = strjoin_gnl(&content, "\"");
			break ;
		}
		i++;
	}
	index = &i;
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
		if (!content)
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
