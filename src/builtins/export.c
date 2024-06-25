/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:12 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/25 17:20:53 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_err(char *str)
{
	ft_printf(2, "minishello: export: `%s': not a valid identifier\n", str);
}
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

static int	export_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || !ft_isalpha(str[0]))
		return (export_err(str), 0);
	if (!val_check(str))
		return (1);
	while (str && str[i])
	{
		if ((str[i] == '=') && (!ft_isalpha(str[i - 1])))
			return (export_err(str), 0);
		i++;
	}
	return (1);	
}

static void	print_export(t_list *envp)
{
	t_list *tmp;

	tmp = envp;
	while (tmp != NULL)
    {
        if (tmp->content != NULL)
            ft_printf(1, "declare -x %s\n", tmp->content);
        else
		    ft_printf(1, "(null)\n");	
        tmp = tmp->next;
    }
}

int	builtin_export(t_input *cmd_line, t_list *envp)
{
	bool	error;

	error = false;
	if (!cmd_line->next)
		return (print_export(envp), 0);
	cmd_line = cmd_line->next;
	while (cmd_line && cmd_line->token == ARG)
	{
		if (!export_syntax(cmd_line->content))
			error = true;
		else
			add_node_env(&envp, cmd_line->content);
		cmd_line = cmd_line->next;
	}
	if (error)
		return (1);
	return (0);
}