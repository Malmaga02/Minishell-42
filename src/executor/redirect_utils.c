/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:00:45 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/16 11:39:46 by lotrapan         ###   ########.fr       */
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

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_printf(2, "%s: permission denied\n", path), -1);
	return (fd);
}

int	handle_append_output(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_printf(2, "%s: permission denied\n", path), -1);
	return (fd);
}

void	close_exec_fd(void)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}
