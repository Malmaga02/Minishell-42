/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:02:54 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 17:46:36 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_uatoi(const char *str)
{
	int					i;
	int					sign;
	unsigned int		n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	numeric_check(t_input *cmd_line)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = cmd_line;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		while (tmp->content[i])
		{
			if (tmp->content[i] == '-' || tmp->content[i] == '+')
				i++;
			if (!ft_isdigit(tmp->content[i]))
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	builtin_exit(t_all *shell, t_input *cmd_line)
{
	g_status_code = 0;
	ft_printf(1, "exit\n");
	if (dll_input_size(cmd_line) != 1)
	{
		if (dll_input_size(cmd_line) > 2)
		{
			g_status_code = 1;
			return ((ft_printf(2, "minishell: exit: too many arguments\n")), 1);
		}	
		else if (numeric_check(cmd_line) == 0)
		{
			ft_printf(2, "minishell: exit: rrt: numeric argument required\n");
			g_status_code = 2;
		}
	}
	if (dll_input_size(cmd_line) == 2 && g_status_code != 2)
		g_status_code = ft_uatoi(cmd_line->next->content);
	free_all(shell);
	exit(g_status_code);
}
