/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_merged_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:16:51 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:28 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_merge_next(int *merge_arr, int i, int size)
{
	int	res;

	res = 1;
	while (i < size && merge_arr[i++] == MERGE_NEXT)
		res++;
	return (res - 1);
}

char	*delete_empty_env(char	*mtx_cmdline)
{
	if (ft_strlen(mtx_cmdline) == 1 && !ft_strncmp(mtx_cmdline, "$", 2))
		return (free(mtx_cmdline), ft_strdup(""));
	return (mtx_cmdline);
}

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

int	*organize_merge_arr(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i != 0 && (arr[i] == MERGE_PREV || arr[i] == MERGE_BOTH))
		{
			arr[i - 1] = MERGE_NEXT;
			if (arr[i] == MERGE_PREV)
				arr[i] = STAY;
			else if (arr[i] == MERGE_BOTH)
				arr[i] = MERGE_NEXT;
		}
		i++;
	}
	return (arr);
}

int	*find_index(int index, int *merge_arr, int size)
{
	int	*new_index;
	int	i;

	i = index;
	while (i < size && merge_arr[i] == MERGE_NEXT)
		i++;
	i = i - 1;
	new_index = &i;
	return (new_index);
}
