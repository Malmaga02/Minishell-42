/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_args_mtx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:16:51 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:28 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_if_cmd_before_red(t_input *head, t_input *cmdline)
{
	int	cmd;

	cmd = 0;
	while (head != cmdline)
	{
		if (head->token == CMD)
			cmd = 1;
		if (find_token_type(head->token) == OPERATORS && cmd)
			cmd = 0;
		head = head->next;
	}
	return (cmd);
}

int	count_args_redirect(t_input *cmdline, int if_cmd_before_red)
{
	int	len;

	len = 0;
	if (if_cmd_before_red)
	{
		while (cmdline && (cmdline->token == FILE_W
				|| cmdline->token == ARG))
		{
			cmdline = cmdline->next;
			len++;
		}
		return (len);
	}
	while (cmdline && (cmdline->token != CMD))
	{
		cmdline = cmdline->next;
		len++;
	}
	return (len);
}

int	count_args(t_input *cmdline, int token, int if_cmd_before_red)
{
	int	len;

	len = 1;
	if (token == CMD)
	{
		cmdline = cmdline->next;
		while (cmdline && cmdline->token == ARG)
		{
			cmdline = cmdline->next;
			len++;
		}
	}
	else if (check_which_operator(token) == REDIRECTS)
		len = count_args_redirect(cmdline, if_cmd_before_red);
	return (len);
}

char	**complete_args(t_input *cmdline, int flag, char **args, int index)
{
	while (cmdline && (args && args[index]))
	{
		if (flag && !(cmdline->token == FILE_W || cmdline->token == ARG))
			break ;
		else if (!flag && cmdline->token == CMD)
		{
			args[index] = cmdline->content;
			if (!args[index])
				return (NULL);
			break ;
		}
		args[index] = cmdline->content;
		if (!args[index])
			return (NULL);
		cmdline = cmdline->next;
		index++;
	}
	return (args);
}
