/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:46 by lotrapan          #+#    #+#             */
/*   Updated: 2024/02/21 18:14:00 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close_fd(int fd)
{
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}
/*Parameters
	fd: The file descriptor to close.*/