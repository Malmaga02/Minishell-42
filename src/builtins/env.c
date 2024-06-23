/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:21 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/23 17:33:51 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *envp)
{
	t_list *tmp;

	tmp = envp;
	while (tmp != NULL)
    {
        if (tmp->content != NULL)
            ft_printf(1, "%s\n", tmp->content);
        else
            ft_printf(1, "(null)\n");
        tmp = tmp->next;
    }
}

int		builtin_env(t_input *cmd, t_list *envp)
{
	if (dll_input_size(cmd) > 1)
	{
		ft_printf(2, "env: '%s' : No such file or directory\n", cmd->next->content);
		return (127);
	}
    print_env(envp);
	return (1);
}