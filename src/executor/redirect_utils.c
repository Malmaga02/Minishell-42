/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:00:45 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 19:05:44 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_validation_input(t_input *cmd_line)
{
	t_input	*current;

	current = cmd_line;
	while (current)
	{
		if (current->token == R_INPUT)
		{
			if (!syntax_validation(current->args) || !file_validation(current->args))
				return (0);
			if (!handle_input(current->args))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	redirect_validation_output(t_input *cmd_line)
{
	t_input	*current;

	current = cmd_line;
	while (current)
	{
		if (current->token == R_OUTPUT || current->token == D_RED_OUTPUT)
		{
			if (!syntax_validation(current->args))
				return (0);
			if (current->token == R_OUTPUT)
			{
				if (!handle_output(current->args))
					return (0);
        	}
			else if (current->token == D_RED_OUTPUT)
			{
        	    if (!handle_append_output(current->args))
					return (0);
        	}
		}
		current = current->next;
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

int	get_last_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
