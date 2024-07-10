/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:21 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/10 11:30:13 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *envp)
{
	t_list	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		if (equal_check(tmp->content) != 0)
		{
			if (tmp->content != NULL)
				ft_printf(1, "%s\n", tmp->content);
			else
				ft_printf(1, "(null)\n");
		}
		tmp = tmp->next;
	}
}

void	builtin_env(t_all *shell)
{
	char	**av;

	av = shell->cmd_line->args;
	if (av[1])
	{
		ft_printf(2, "env: '%s' : No such file or directory\n",
			av[1]);
		g_status_code = 127;
		return ;
	}
	print_env(shell->envp);
	g_status_code = 1;
}
