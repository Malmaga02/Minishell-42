/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:02:57 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/22 12:07:55 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_rep_check(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	print_echo(char **av, int i)
{
	while (av && av[i])
	{
		ft_printf(1, "%s", av[i]);
		if (av[i + 1])
			ft_printf(1, " ");
		i++;
	}
}

void	builtin_echo(char **av)
{
	bool	flag;
	int		i;

	i = 1;
	g_status_code = 0;
	flag = false;
	if (!av[i])
	{
		ft_printf(1, "\n");
		return ;
	}
	while (av && av[i][0] == '-' && (ft_strlen(av[i]) > 1))
	{
		if (char_rep_check(av[i], 'n'))
			flag = true;
		else
			break ;
		i++;
	}
	print_echo(av, i);
	if (!flag)
		ft_printf(1, "\n");
}
