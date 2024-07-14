/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:05 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/14 17:06:05 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env_variable(t_list **envp, char *word)
{
	t_list	*tmp;
	t_list	*prev;
	char	*str;

	str = NULL;
	if (envp == NULL || *envp == NULL || word == NULL)
		return ;
	tmp = *envp;
	prev = NULL;
	while (tmp != NULL)
	{
		str = (char *)tmp->content;
		if (ft_strncmp(str, word, ft_strlen(word)) == 0
			&& str[ft_strlen(word)] == '=')
		{
			if (prev == NULL)
				*envp = tmp->next;
			else
				prev->next = tmp->next;
			return (free(tmp->content), free(tmp));
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static void	print_err(char *str)
{
	ft_printf(2, "minishello: unset: %s : not a valid identifier\n", str);
}

static int	syntax_check(char **av)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (av[j])
	{
		if ((av[j][0] != '_') && (!ft_isalpha(av[j][0])))
			return (print_err(av[j]), 0);
		while (av[j] && av[j][i])
		{
			if (!ft_isalnum(av[j][i]) && av[j][i] != '_')
				return (print_err(av[j]), 0);
			i++;
		}
		j++;
	}
	return (1);
}

int	builtin_unset(char **av, t_list *envp)
{
	int	i;

	i = 1;
	g_status_code = 0;
	if (!av[i])
		return (0);
	if (!syntax_check(av))
		return (g_status_code = 1, 1);
	while (av && av[i])
	{
		del_env_variable(&envp, av[i]);
		i++;
	}
	return (0);
}
