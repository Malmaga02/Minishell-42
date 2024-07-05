/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:30:01 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 19:06:05 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_all *shell, bool start)
{
	t_input *current;

	current = shell->cmd_line;
	if (start)
	{
		//heredoc
		if (!redirect_validation_input(current))
			return (0);
		if (!redirect_validation_output(current))
			return (0);
	}
    return (1);
}

int	handle_input(char **args)
{
	int	i;
	int	new_in_fd;

	i = get_last_args(args);
	new_in_fd = open(args[i], O_RDONLY);
    if (new_in_fd < 0)
        return (ft_printf(2, "open\n"), 0);
    if (dup2(new_in_fd, STDIN_FILENO) == -1) 
	{
        close(new_in_fd);
        return (ft_printf(2, "dup2\n"), 0);
    }
    close(new_in_fd);
	return (1);
}

int	handle_output(char **args)
{
	int	i;
	int	new_out_fd;

	i = get_last_args(args);
	new_out_fd = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (new_out_fd < 0)
        return (ft_printf(2, "open\n"), 0);
    if (dup2(new_out_fd, STDOUT_FILENO) == -1)
	{
        close(new_out_fd);
        return (ft_printf(2, "dup2\n"),0);
    }
    close(new_out_fd);
	return (1);
}

int	handle_append_output(char **args)
{
	int	i;
	int	new_out_fd;

	i = get_last_args(args);
	new_out_fd = open(args[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (new_out_fd < 0)
        return (ft_printf(2, "open\n"), 0);
    if (dup2(new_out_fd, STDOUT_FILENO) == -1) 
	{
        close(new_out_fd);
        return (ft_printf(2, "dup2\n"),0);
    }
    close(new_out_fd);
	return (1);
}
