/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:28:17 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:28:31 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_args_red(t_input *cmdline, char **args, int if_cmd_before_red)
{
	int	i;

	i = 0;
	if (cmdline && check_which_operator(cmdline->token) == REDIRECTS)
	{
		args[i] = cmdline->content;
		if (!args[i])
			return (free(args), NULL);
		cmdline = cmdline->next;
		i++;
	}
	args = complete_args(cmdline, if_cmd_before_red, args, i);
	if (!args)
		return (free(args), NULL);
	return (args);
}

char	**get_args_cmds(t_input *cmdline)
{
	const int	len = count_args(cmdline, cmdline->token, 0);
	int			i;
	char		**args;

	i = 0;
	args = ft_calloc(len + 1, sizeof(char *));
	if (!args)
		return (NULL);
	if (cmdline && cmdline->token == CMD)
	{
		args[i] = cmdline->content;
		if (!args[i])
			return (free(args), NULL);
		cmdline = cmdline->next;
		i++;
	}
	while (cmdline && cmdline->token == ARG)
	{
		args[i] = cmdline->content;
		if (!args[i])
			return (free(args), NULL);
		cmdline = cmdline->next;
		i++;
	}
	return (args);
}

char	**get_args_redirects(t_input *cmdline, t_input *head)
{
	int		len;
	int		i;
	int		if_cmd_before_red;
	char	**args;

	i = 0;
	if_cmd_before_red = find_if_cmd_before_red(head, cmdline);
	len = count_args(cmdline, cmdline->token, if_cmd_before_red);
	args = ft_calloc(len + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args = handle_args_red(cmdline, args, if_cmd_before_red);
	if (!args)
		return (NULL);
	return (args);
}

t_input	*get_args_mtx(t_input *cmd_line)
{
	t_input	*cmdline;
	t_input	*current;

	current = NULL;
	cmdline = cmd_line;
	while (cmdline)
	{
		cmdline->args = NULL;
		if (!(cmdline->token == CMD
				|| check_which_operator(cmdline->token) == REDIRECTS))
		{
			cmdline = cmdline->next;
			continue ;
		}
		if (cmdline->token == CMD)
			cmdline->args = get_args_cmds(cmdline);
		else if (check_which_operator(cmdline->token) == REDIRECTS)
			cmdline->args = get_args_redirects(cmdline, cmd_line);
		if (!cmdline->args)
			return (dll_input_clear(&cmd_line), NULL);
		cmdline = cmdline->next;
	}
	return (cmd_line);
}
