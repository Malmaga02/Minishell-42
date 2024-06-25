/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:51:31 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/25 17:15:47 by lotrapan         ###   ########.fr       */
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


/* static size_t	ft_strlcpy_skip(char *dst, const char *src, size_t size, int skip)
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
} */

t_list	*change_env_variable(t_list *envp, char *var, char *new)
{
	t_list	*tmp;
	int		len_var;
	int		len_new;

	tmp = envp;
	len_var = ft_strlen(var);
	len_new = ft_strlen(new);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len_var) == 0)
		{
			free(tmp->content);
			tmp->content = malloc(sizeof(char) * (len_var + len_new + 1));
			ft_strlcpy(tmp->content, var, len_var + 1);
			ft_strlcpy(tmp->content + len_var, new, len_new + 1);
			return (envp);
		}
		tmp = tmp->next;
	}
	return (envp);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1 && s2) && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}


void	add_node_env(t_list **envp, char *str)
{
	t_list	*new_node;
	t_list	*tmp;
	
	tmp = *envp;
	new_node = ft_lstnew(str);
	if (!new_node)
		return ;
	ft_lstadd_back(&tmp, new_node);
}