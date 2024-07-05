/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:30:01 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 12:13:23 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_all *shell)
{
	t_input *current;

	current = shell->cmd_line;
	if (!redirect_validation(current))
		return (0);
    while (current)
	{
        if (current->token == R_INPUT)
		{
			if (!handle_input(current->args))
				return (0);
        } 
		else if (current->token == R_OUTPUT)
		{
			if (!handle_output(current->args))
				return (0);
        }
		else if (current->token == D_RED_OUTPUT)
		{
            if (!handle_append_output(current->args))
				return (0);
        }
        current = current->next;
    }
    return (1);
}

int	handle_input(char **args)
{
	int	i;
	int	fd;

	i = get_last_args(args);
	fd = open(args[i], O_RDONLY);
    if (fd < 0)
        return (ft_printf(2, "open\n"), 0);
    if (dup2(fd, STDIN_FILENO) == -1) 
	{
        close(fd);
        return (ft_printf(2, "dup2\n"), 0);
    }
    close(fd);
	return (1);
}

int	handle_output(char **args)
{
	int	i;
	int	fd;

	i = get_last_args(args);
	fd = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (ft_printf(2, "open\n"), 0);
    if (dup2(fd, STDOUT_FILENO) == -1) 
	{
        close(fd);
        return (ft_printf(2, "dup2\n"),0);
    }
    close(fd);
	return (1);
}

int	handle_append_output(char **args)
{
	int	i;
	int	fd;

	i = get_last_args(args);
	fd = open(args[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return (ft_printf(2, "open\n"), 0);
    if (dup2(fd, STDOUT_FILENO) == -1) 
	{
        close(fd);
        return (ft_printf(2, "dup2\n"),0);
    }
    close(fd);
	return (1);
}
