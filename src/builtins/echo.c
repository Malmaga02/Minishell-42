/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:02:57 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/18 19:59:13 by lotrapan         ###   ########.fr       */
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

void	print_echo(t_input *tmp)
{
	while (tmp)
	{
		ft_printf(1, "%s", tmp->content);
		if (tmp->next)
			ft_printf(1, " ");
		tmp = tmp->next;
	}
}

void	builtin_echo(t_input *cmd_line)
{
	t_input	*tmp;
	bool	flag;

	tmp = cmd_line;
	flag = false;
	if (!tmp->next)
	{
		ft_printf(1, "\n");
		return ;
	}
	tmp = tmp->next;
	while (tmp && tmp->content[0] == '-' && (ft_strlen(tmp->content) > 1))
	{
		if (char_rep_check(tmp->content, 'n') && !flag)
			flag = true;
		else
			break ;
		tmp = tmp->next;
	}
	print_mtx(tmp->args);
	if (!flag)
		ft_printf(1, "\n");
	return ;
}
