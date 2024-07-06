/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:03:05 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 17:16:53 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void del_env_variable(t_list **envp, char *word)
{
    t_list *tmp;
    t_list *prev;
    char *str;

    if (envp == NULL || *envp == NULL || word == NULL)
        return ;
    tmp = *envp;
    prev = NULL;
    while (tmp != NULL)
    {
        str = (char *)tmp->content;
        if (ft_strncmp(str, word, ft_strlen(word)) == 0 && str[ft_strlen(word)] == '=')
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

static int syntax_check(char **av)
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

int	builtin_unset(t_input *cmd, t_list *envp)
{
	g_status_code = 0;
	if ((cmd->next && cmd->next->token != ARG) || (!cmd->next))
		return (0);
	if (!syntax_check(cmd->args))
		return (g_status_code = 1, 1);
	cmd = cmd->next;
	while (cmd && cmd->token == ARG)
	{
		del_env_variable(&envp, cmd->content);
		cmd = cmd->next;
	}
	return (0);
}
