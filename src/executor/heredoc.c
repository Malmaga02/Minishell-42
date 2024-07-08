/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:10:27 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/08 12:11:07 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_validation(t_input *cmd_line)
{
	t_input *current;

	current = cmd_line;
	while (current)
	{
		if (current->token == D_RED_INPUT)
		{
			if (!syntax_validation(current->args))
				return (0);
			open_heredoc(current->args);
		}
		current = current->next;
	}
	return (1);
}

void	open_heredoc(char **args)
{
	char		*line;
	const char	*delimiter = args[1];

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || strcmp(line, delimiter) == 0)
			return (free(line));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free(line);
	}
}
