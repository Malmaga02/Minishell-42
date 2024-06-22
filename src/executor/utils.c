/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:51:31 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/22 16:59:56 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_mtx(void *lst, bool is_input) // cambiare fun che accetta sia t_input che t_list
{
	int		i;
	int		len;
	char	**mtx;
	t_input *input_lst = NULL;
    t_list *list_lst = NULL;

	i = 0;
	if (is_input)
	{
		input_lst = (t_input *)lst;
		len = dll_input_size(input_lst);
	}
	else
	{
		list_lst = (t_list *)lst;
		len = ft_lstsize(list_lst);
	}
	mtx = malloc(sizeof(char *) * (len + 1));
	if (!mtx)
		return (NULL);
	if (is_input)
	{
		while (input_lst)
		{
			mtx[i] = ft_strdup(input_lst->content);
			i++;
			input_lst = input_lst->next;
		}
	}
	else
	{
		while (list_lst)
		{
			mtx[i] = ft_strdup(list_lst->content);
			i++;
			list_lst = list_lst->next;
		} 
	}
	mtx[i] = NULL;
	return(mtx);
}


static size_t	ft_strlcpy_skip(char *dst, const char *src, size_t size, int skip)
{
	size_t	i;

	if (size == 0 || !src[skip])
		return (ft_strlen(src));
	i = skip;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return ((size_t)ft_strlen(src));
}

void	change_env_variable(t_list *envp, char *var, char *new)
{
	t_list	*tmp;
	int		len;

	tmp = envp;
	len = ft_strlen(var);
	if (!new)
		return ;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len) == 0)
		{
			ft_strlcpy_skip(tmp->content, new, ft_strlen(new) + 1, len + 1);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	print_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx && mtx[i])
	{
		printf("%s\n", mtx[i]);
		i++;
	}
}