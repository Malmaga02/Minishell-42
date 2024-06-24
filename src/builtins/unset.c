/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:05 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/24 18:24:10 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_syntax(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	del_env_variable(t_list **envp, char *word)
{
	char	*str;
	t_list	*tmp;

	str = NULL;
	tmp = *envp;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (ft_strcmp(str, word) == 0)
		{
			*envp = tmp->next;
			free(tmp);
		}
		else
			tmp = *envp;
		tmp = tmp->next;
	}
	return ;
}
static void	print_err(char *str)
{
	ft_printf(2, "minishello: unset: %s : not a valid identifier\n", str);
}

static int syntax_check(char **av)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (av[j])
	{
		if ((ft_isdigit(av[j][0])) || (!unset_syntax(av[j])))
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
int	builtin_unset(t_input *cmd, t_list *envp)
{
	if ((cmd->next && cmd->next->token != ARG) || (!cmd->next))
		return (0);
	if (!syntax_check(cmd->args))
		return (1);
	cmd = cmd->next;
	while (cmd && cmd->token == ARG)
	{
		del_env_variable(&envp, cmd->content);
		cmd = cmd->next;
	}
	return (0);
}
