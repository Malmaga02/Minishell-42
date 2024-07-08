/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:12 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/08 12:08:38 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_err(char *str, int *error)
{
	*error = 1;
	ft_printf(2, "minishello: export: `%s': not a valid identifier\n", str);
}

static int	export_syntax(char *str, int *error)
{
	int	i;

	i = 0;
	if ((str[0] != '_') && (!ft_isalpha(str[0])))
		return (export_err(str, error), 0);
	if (!equal_check(str))
		return (1);
	while (str && str[i])
	{
		if ((str[i] == '=') && (str[i - 1] == '+'))
			return (1);
		if ((str[i] == '=') && (!char_check(str, error)))
			return (export_err(str, error), 0);
		i++;
	}
	return (1);
}

void	print_export(t_list *envp)
{
	t_list	*tmp;

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

void	export_add(t_all *shell)
{
	int		i;
	t_list	*tmp;
	char	*str;

	str = shell->cmd_line->content;
	i = equal_check(str);
	if ((i > 0 && str[i - 1] == '+'))
		change_node_env(&shell->envp, str, i);
	else if (doppelganger_check(shell->envp, str, i))
	{
		tmp = find_node_in_env(shell->envp, str, i);
		free(tmp->content);
		tmp->content = malloc(sizeof(char) * (ft_strlen(str) + 1));
		ft_strlcpy(tmp->content, str, (ft_strlen(str) + 1));
	}
	else
		add_node_env(&shell->envp, str);
}

int	builtin_export(t_all *shell)
{
	int	error;

	g_status_code = 0;
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
		return (g_status_code = 1, 1);
	return (0);
}
