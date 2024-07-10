/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:30:01 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/10 18:33:38 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_all *shell)
{
	t_input *current;

	current = shell->cmd_line;
	current = set_std_cmd_line(current);
	/* if (!redirect_validation(current))
		return (0); */
	//printf("FORZA\n");
    while (current)
	{
        if (current->token == R_INPUT)
		{
			if (!handle_input(current))
				return (0);
        } 
		else if (current->token == R_OUTPUT)
		{
			if (!handle_output(current))
				return (0);
        }
		else if (current->token == D_RED_OUTPUT)
		{
            if (!handle_append_output(current))
				return (0);
        }
        current = current->next;
    }
    return (1);
}

int	handle_input(t_input *current)
{
	int	fd;

	fd = open(current->args[1], O_RDONLY);
    if (fd < 0)
        return (ft_printf(2, "Error: open\n"), 0);
	//put_fd_in_cmd(current, fd);
    close(fd);
	return (1);
}

int	handle_output(t_input *current)
{
	int	fd;

	fd = open(current->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (ft_printf(2, "Error: open\n"), 0);
	current->fd_out = dup(fd);
    close(fd);
	return (1);
}

int	handle_append_output(t_input *current)
{
	int	fd;

	fd = open(current->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return (ft_printf(2, "Error: open\n"), 0);
    current->fd_out = dup(fd);
    close(fd);
	return (1);
}
