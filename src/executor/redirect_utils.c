/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:00:45 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/12 16:40:57 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_fd_cmd(t_all *shell, int *last_fdin, int *last_fdout)
{
    t_input *current;

    current = shell->cmd_line;
    while (current && current->prev)
    {
        if (current->token == PIPE)
            break;
        if (current->token == CMD)
        {
            current->fd_in = last_fdin;
            current->fd_out = last_fdout;
            return;
        }
        current = current->prev;
    }
    while (current && current->next)
    {
        if (current->token == PIPE)
            break;
        if (current->token == CMD)
        {
            current->fd_in = last_fdin;
            current->fd_out = last_fdout;
            return;
        }
        current = current->next;
    }
}

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
		if (tmp->token == CMD)
		{
			tmp->fd_in = malloc(sizeof(int *));
			tmp->fd_out = malloc(sizeof(int *));
			if (!tmp->fd_in || !tmp->fd_out)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (current);
}
