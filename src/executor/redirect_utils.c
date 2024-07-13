/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:00:45 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/13 15:30:09 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(char *path)
{
	int	fd;

	if (access(path, F_OK))
		return (ft_printf(2, "%s: No such file or directory\n", path), -1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
        return (ft_printf(2, "%s: permission denied\n", path), -1);
	return (fd);
}

int	handle_output(char *path)
{
	int	fd;

	if (access(path, F_OK))
		return (ft_printf(2, "%s: No such file or directory\n", path), -1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
        return (ft_printf(2, "%s: permission denied\n", path), -1);
	return (fd);
}

int	handle_append_output(char *path)
{
	int	fd;
	
	if (access(path, F_OK))
		return (ft_printf(2, "%s: No such file or directory\n", path), -1);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
        return (ft_printf(2, "%s: permission denied\n", path), -1);
	return (fd);
}

/* void set_fd_cmd(t_all *shell, int *last_fdin, int *last_fdout)
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
} */

/* t_input *set_std_cmd_line(t_input *current)
{
	t_input *tmp;

	tmp = current;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			tmp->fd_in = malloc(sizeof(int));
			tmp->fd_out = malloc(sizeof(int));
			if (!tmp->fd_in || !tmp->fd_out)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (current);
} */
