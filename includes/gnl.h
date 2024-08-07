/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:46:24 by chsassi           #+#    #+#             */
/*   Updated: 2024/07/20 18:21:08 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

char	*gnl(int fd);
int		strlen_gnl(char *str);
void	*calloc_gnl(size_t nmemb, size_t size);
char	*strjoin_gnl(char **s1, char *s2);
int		strchr_gnl(char *s, int c);
char	*substr_gnl(char *s, size_t start, size_t end);

#endif
