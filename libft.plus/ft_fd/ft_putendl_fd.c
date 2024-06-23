/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:05:12 by lotrapan          #+#    #+#             */
/*   Updated: 2024/02/21 18:14:40 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_s_fd(char *s)
{
	if (s == NULL)
	{
		return (-1);
	}
	return (1);
}

static int	ft_check_fd(int fd)
{
	if (fd < 0)
	{
		return (-1);
	}
	return (1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (ft_check_s_fd(s) == -1 || ft_check_fd(fd) == -1)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/*Parameters
	s: The string to output.
	fd: The file descriptor on which to write.
Return value
	None
External functs.
	write
Description
	Outputs the string ’s’ to the given file descriptor
	followed by a newline.*/