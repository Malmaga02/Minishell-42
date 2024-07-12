/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:30:01 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/12 16:41:16 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_input *current, int *last_fdin, int *last_fdout)
{
	if (current->token == R_INPUT)
	{
		if ((*last_fdin = handle_input(current)) == -1)
			return (0);
    } 
	else if (current->token == R_OUTPUT)
	{
		if ((*last_fdout = handle_output(current)) == -1)
			return (0);
    }
	else if (current->token == D_RED_OUTPUT)
	{
           if ((*last_fdout = handle_append_output(current)) == -1)
			return (0);
    }
	return (1);
}

int	handle_redirect(t_all *shell)
{
	t_input *current;
	int		*last_fdin;
	int 	*last_fdout;
	bool	redirect;

	current = shell->cmd_line;
	last_fdin = malloc(sizeof(int *));
	last_fdout = malloc(sizeof(int *));
	if (!last_fdout || !last_fdin)
		return (0);
	redirect = false;
	current = set_std_cmd_line(current);
	if (!current)
		return (0);
    while (current)
	{
		if (current->token == R_INPUT || current->token == R_OUTPUT || current->token == D_RED_OUTPUT)
		{
			redirect = true;
			if (!check_redirect(current, last_fdin, last_fdout))
				return (0);
		}
		if (redirect && (!current->next || current->next->token == PIPE))
		{
			set_fd_cmd(shell, last_fdin, last_fdout);
			last_fdin = NULL;
			last_fdout = NULL;
			redirect = false;
		}
        current = current->next;
    }
    return (1);
}

int	handle_input(t_input *current)
{
	int	fd;

	if ((fd = open(current->args[1], O_RDONLY)) == -1)
        return (ft_printf(2, "Error: open\n"), 0);
    close(fd);
	return (fd);
}

int	handle_output(t_input *current)
{
	int	fd;

	if ((fd = open(current->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        return (ft_printf(2, "Error: open\n"), 0);
    close(fd);
	return (fd);
}

int	handle_append_output(t_input *current)
{
	int	fd;

	if ((fd = open(current->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
        return (ft_printf(2, "Error: open\n"), 0);
    close(fd);
	return (fd);
}
