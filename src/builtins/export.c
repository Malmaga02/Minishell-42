/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:12 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/01 18:08:45 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_err(char *str, int *error)
{
	*error = 1;
	ft_printf(2, "minishello: export: `%s': not a valid identifier\n", str);
}

static int	export_syntax(char *str, int *error)
{
	int	i;

	i = 0;
	if (str[0] == '=' || !ft_isalpha(str[0]))
		return (export_err(str, error), 0);
	if (!equal_check(str))
		return (1);
	while (str && str[i])
	{
		if ((str[i] == '=') && (str[i - 1] == '+'))
			return (1);
		if ((str[i] == '=') && (!ft_isalpha(str[i - 1])))
			return (export_err(str, error), 0);
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

static void	export_add(t_all *shell)
{
	int	i;
	t_list *tmp;

	i = equal_check(shell->cmd_line->content);
	if ((i > 0 && shell->cmd_line->content[i - 1] == '+'))
		change_node_env(&shell->envp, shell->cmd_line->content, i);
	else if (doppelganger_check(shell->envp, shell->cmd_line->content, i))
	{
		tmp = find_node_in_env(shell->envp, shell->cmd_line->content, i);
		free(tmp->content);
		tmp->content = malloc(sizeof(char) * (ft_strlen(shell->cmd_line->content) + 1));
		ft_strlcpy(tmp->content, shell->cmd_line->content, (ft_strlen(shell->cmd_line->content) + 1));
	}
	else
		add_node_env(&shell->envp, shell->cmd_line->content);
}

int	builtin_export(t_all *shell)
{
	int	error;
	
	error = 0;
	if (!shell->cmd_line->next)
		return (print_export(shell->envp), 0);
	shell->cmd_line = shell->cmd_line->next;
	while (shell->cmd_line && shell->cmd_line->token == ARG)
	{
		if (export_syntax(shell->cmd_line->content, &error))
			export_add(shell);
		shell->cmd_line = shell->cmd_line->next;
	}
	if (error)
		return (1);
	return (0);
}
