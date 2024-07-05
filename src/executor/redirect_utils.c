/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:00:45 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 11:37:10 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	redirect_validation(t_input *cmd_line)
{
	while (cmd_line)
	{
		if (cmd_line->token == R_INPUT)
		{
			if (!syntax_validation(cmd_line->args) || !file_validation(cmd_line->args))
				return (0);
		}
		else if (cmd_line->token == R_OUTPUT || cmd_line->token == D_RED_OUTPUT)
		{
			if (!syntax_validation(cmd_line->args))
				return (0);
		}
		cmd_line = cmd_line->next;
	}
	return (1);
}

int	file_validation(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (open(args[i], O_RDONLY) < 0)
			return (ft_printf(2, "minishell: %s: No such file or directory\n", args[i]), 0);
		i++;
	}
	return (1);
}

int	syntax_validation(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\0')
			return (ft_printf(2, "minishell: syntax error near unexpected token `newline'\n"), 0);
		i++;
	}
	return (1);
}
