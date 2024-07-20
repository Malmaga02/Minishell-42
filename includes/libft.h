/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:42:47 by chsassi           #+#    #+#             */
/*   Updated: 2024/07/20 18:19:03 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "gnl.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>

# define FD_MAX 4096

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dll
{
	int				value;
	int				index;
	struct s_dll	*prev;
	struct s_dll	*next;
}					t_dll;

/* CHAR HANDLING */
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_toupper(int c);
int					ft_tolower(int c);

/* CONVERSIONS */
long				ft_atol(const char *str);
int					ft_atoi(const char *str);
int					ft_atoi_base(char *str, char *base);
char				*ft_itoa(int nb);
int					ft_putnbr_fd(int n, int fd);

/* LIST HANDLING */

// Linked Lists
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

// Double Linked Lists
void				dll_add_back(t_dll **lst, t_dll *new);
void				dll_add_front(t_dll **lst, t_dll *new);

t_dll				*dll_iterate(t_dll *lst);

t_dll				*dll_last(t_dll *lst);

void				dll_clear(t_dll **lst);
t_dll				*dll_new(int value);
int					dll_size(t_dll *lst);
int					find_min_index(t_dll *pStack);

int					find_min_value(t_dll *pStack);

int					find_max_index(t_dll *pStack);

int					find_max_value(t_dll *pStack);

void				set_index(t_dll **list);

/* MATRIX HANDLING */
char				**copy_mtx(char **mtx);
int					count_cols(char **mtx);
int					count_elements(char **mtx, char c);
int					count_rows(char **mtx);
char				**mtx_alloc(int rows, int cols);
void				reset_matrix_to_x(char **mtx, int cols, int rows);

/* MEMORY MANAGEMENT */
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t len);

/* STRING HANDLING */
void				ft_bzero(void *s, size_t n);

int					ft_isint(char *str);
int					ft_putstr_fd(char *s, int fd);
char				**ft_split(const char *str, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);

int					ft_putnbrbase_wrapper_fd(uintptr_t nbr, char *base, int fd);

int					ft_putunsigned_fd(unsigned int n, int fd);

int					ft_puthex_fd(unsigned int num, char format, int fd);

int					ft_putptr_fd(uintptr_t ptr, int fd);

#endif
