/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:02:54 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/18 15:51:58 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_uatoi(const char *str, int *error)
{
	int				i;
	int				sign;
	unsigned int	n;
	unsigned int	check;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = n;
		n = n * 10 + (str[i] - '0');
		if (check > n)
			return (*error = 1, 0);
		i++;
	}
	return (n * sign);
}

int	numeric_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av && av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] == '-' || av[i][j] == '+')
				j++;
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	builtin_exit(t_all *shell, char **av)
{
	int	error;

	error = 0;
	g_status_code = 0;
	ft_printf(1, "exit\n");
	if (mtx_size(av) != 1)
	{
		g_status_code = ft_uatoi(av[1], &error);
		if (numeric_check(av) == 0 || error == 1)
		{
			ft_printf(2, "minishell: exit: rrt: numeric argument required\n");
			g_status_code = 2;
		}
		else if (mtx_size(av) > 2)
		{
			g_status_code = 1;
			return ((ft_printf(2, "minishell: exit: too many arguments\n")), 1);
		}
	}
	free_all(shell);
	exit(g_status_code);
}
