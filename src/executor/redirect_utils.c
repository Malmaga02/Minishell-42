/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:00:45 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/10 18:28:28 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	redirect_validation(t_input *cmd_line)
{
	t_input	*current;

	current = cmd_line;
	if (!heredoc_validation(current))
		return (0); 
	while (current)
	{
		if (current->token == R_INPUT)
		{
			if (!file_validation(current))
				return (0);
		}
		else if (current->token == R_OUTPUT || current->token == D_RED_OUTPUT)
		{
			if (!current->args)
				return (error_validation(), 0);
		}
		current = current->next;
	}
	return (1);
} */

int	file_validation(t_input *current)
{
	int i;
	char **av;

	i = 0;
	av = current->args;
	while (av && av[i])
	{
		if (open(av[i], O_RDONLY) < 0)
			return (ft_printf(2, "minishell: %s: No such file or directory\n", av[i]), 0);
		i++;
	}
	return (1);
}

int	get_last_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

t_input *set_std_cmd_line(t_input *current)
{
	t_input *tmp;

	tmp = current;
	while (tmp)
	{
		current->fd_in = NULL;
		current->fd_out = NULL;
		tmp = tmp->next;
	}
	return (current);
}
