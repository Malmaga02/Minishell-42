/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:05 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/22 16:58:09 by lotrapan         ###   ########.fr       */
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

static void	del_word_in_env(t_list *envp, char *word)
{
	char *str;

	while (envp)
	{
		str = (char *)envp->content;
		if (ft_strncmp(str, word, ft_strlen(word)) == 0)
			ft_lstdelone(envp, free);
		else
			envp = envp->next;
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
			return (print_err(av[j]),0);
		while (av[j] && av[j][i])
		{
			if (!ft_isalnum(av[j][i]) && av[j][i] != '_')
				return (print_err(av[j]),0);
			i++;
		}
	}
	return (1);

}
void	builtin_unset(t_all *shell, t_input *cmd)
{
	if ((cmd->next && cmd->next->token != ARG) || (!cmd->next))
		return ;
	if (!syntax_check(cmd->args))
		return ;
	cmd = cmd->next;
	while (cmd->token == ARG)
	{
		del_word_in_env(shell->envp, cmd->content);
		cmd = cmd->next;
	}
	return ;
}
