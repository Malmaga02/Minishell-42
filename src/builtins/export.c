/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:12 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/23 20:47:34 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	val_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
} 

static void	print_export(t_list *envp)
{
	t_list *tmp;

	tmp = envp;
	while (tmp != NULL)
    {
		if (val_check(tmp->content))
		{
        	if (tmp->content != NULL)
        	    ft_printf(1, "declare -x %s\n", tmp->content);
        	else
			    ft_printf(1, "(null)\n");
		}	
        tmp = tmp->next;
    }
}

int	builtin_export(t_input *cmd_line, t_list *envp)
{
	if (!cmd_line->next)
		print_export(envp);
	if (!syntax_export(cmd_line->args))
		return (ft_printf(2,"bash: export: `': not a valid identifier"), 1);
	return (0);
}