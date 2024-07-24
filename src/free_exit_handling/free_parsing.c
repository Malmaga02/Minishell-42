/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:29:13 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 12:29:15 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsing(t_parsing *parsing)
{
	free(parsing->arr_token);
	parsing->arr_token = NULL;
	free_mtx(parsing->mtx_from_input);
	parsing->mtx_from_input = NULL;
	free(parsing->input);
	parsing->input = NULL;
	free(parsing);
	parsing = NULL;
}

void	set_clear_all(t_all *all)
{
	if (!all->cmd_line)
		return ;
	if (all && all->cmd_line)
	{
		dll_input_clear(&(all->cmd_line));
		all->cmd_line = NULL;
	}
	if (all && all->pipes)
	{
		close_pipes(all);
		free_pipes(all);
	}
	close_exec_fd();
}

void	free_all(t_all *all)
{
	if (all->envp)
	{
		ft_lstclear(&(all->envp), free);
		all->envp = NULL;
	}
	if (all->cmd_line)
	{
		dll_input_clear(&(all->cmd_line));
		all->cmd_line = NULL;
	}
	if (all->pipes)
	{
		close_pipes(all);
		free_pipes(all);
	}
	close_exec_fd();
}

void	close_all(t_all *all)
{
	free_all(all);
	all = NULL;
	exit(0);
}
