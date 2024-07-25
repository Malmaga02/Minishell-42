/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_mtx_and_lists.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:14 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:28 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parsing_list_in_mtx(t_input *cmd_line)
{
	char	**mtx_input;
	int		size;
	int		i;

	size = dll_input_size(cmd_line);
	i = 0;
	mtx_input = ft_calloc(size + 1, sizeof(char *));
	if (!mtx_input)
		return (NULL);
	while (cmd_line && i < size)
	{
		mtx_input[i] = ft_strdup(cmd_line->content);
		if (!mtx_input[i])
			return (free_mtx(mtx_input), NULL);
		i++;
		cmd_line = cmd_line->next;
	}
	mtx_input[i] = NULL;
	return (mtx_input);
}
