/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:34:50 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/16 19:03:19 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing	*parse_input(t_parsing *parsing)
{
	if (!parsing)
		return (NULL);
	parsing->mtx_from_input = get_mtx_from_input(parsing);
	if (!parsing->mtx_from_input)
		return (free_parsing(parsing), NULL);
	parsing->size = count_rows(parsing->mtx_from_input);
	parsing->arr_token = get_arr_token(parsing->mtx_from_input, parsing->size);
	if (!parsing->arr_token)
		return (free_parsing(parsing), NULL);
	return (parsing);
}

t_input	*create_list_from_input(t_parsing *parsing)
{
	t_input	*cmd_line;
	t_input	*node;
	int		size;
	int		i;
	char	*value;

	i = 0;
	size = parsing->size;
	cmd_line = NULL;
	node = NULL;
	while (i < size)
	{
		value = ft_strdup(parsing->mtx_from_input[i]);
		node = dll_input_new(value);
		if (!value || !node)
			return (free(value), dll_input_clear(&cmd_line), free(node), NULL);
		node->fd_in = -1;
		node->fd_out = -1;
		node->token = parsing->arr_token[i];
		dll_input_addback(&cmd_line, node);
		i++;
	}
	cmd_line = check_if_need_merge(parsing, cmd_line);
	return (cmd_line);
}

t_list	*create_list_from_envp(char **envp)
{
	t_list	*envp_list;
	t_list	*node;
	char	**envp_cpy;
	int		i;

	envp_list = NULL;
	node = NULL;
	i = 0;
	envp_cpy = copy_mtx(envp);
	while (envp_cpy && envp_cpy[i])
	{
		node = ft_lstnew(envp_cpy[i]);
		if (!node)
			return (ft_lstclear(&envp_list, free), free(envp_cpy), NULL);
		ft_lstadd_back(&envp_list, node);
		i++;
	}
	free(envp_cpy);
	return (envp_list);
}

t_all	get_all_info(t_all all_info, char *line, char **envp)
{
	t_parsing	*parsing;

	if (!line)
		return ((t_all){0});
	parsing = (t_parsing *)malloc(sizeof(t_parsing));
	if (!parsing)
		return ((t_all){0});
	*parsing = (t_parsing){0};
	parsing->input = ft_strdup(line);
	if (!parsing->input)
		return (free_parsing(parsing), (t_all){0});
	parsing = parse_input(parsing);
	if (!parsing)
		return ((t_all){0});
	all_info.cmd_line = create_list_from_input(parsing);
	if (!all_info.envp)
		all_info.envp = create_list_from_envp(envp);
	if (!all_info.cmd_line || !all_info.envp)
		return (free_parsing(parsing), (t_all){0});
	return (free_parsing(parsing), all_info);
}
