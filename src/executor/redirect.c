/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:30:01 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/22 11:49:48 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_input *cmd, t_input *current, int *last)
{
	int	status;
	int	ret;

	status = 0;
	ret = 1;
	if (current->token == R_INPUT)
		status = handle_input(current->next->content);
	else if (current->token == R_OUTPUT)
		status = handle_output(current->next->content);
	else if (current->token == D_RED_OUTPUT)
		status = handle_append_output(current->next->content);
	if (status == -1)
		ret = 0;
	if (last != NULL)
		*last = status;
	if (status == -1 && cmd)
		cmd->prevent = true;
	if (status == -1)
		g_status_code = 1;
	return (ret);
}

t_input	*find_cmd_in_block(t_input *block)
{
	while (block && block->token != PIPE)
	{
		if (block->token == CMD && block->prevent == false)
			return (block);
		block = block->next;
	}
	return (NULL);
}

bool	handle_block(t_input *block)
{
	t_input	*cmd;
	int		*last_in;
	int		*last_out;

	last_in = NULL;
	last_out = NULL;
	cmd = find_cmd_in_block(block);
	if (cmd)
		last_in = &cmd->fd_in;
	if (cmd)
		last_out = &cmd->fd_out;
	while (block && block->token != PIPE)
	{
		if (block->token == R_INPUT)
		{
			if (!check_redirect(cmd, block, last_in))
				return (false);
		}
		else if ((block->token == R_OUTPUT || block->token == D_RED_OUTPUT)
			&& !check_redirect(cmd, block, last_out))
			return (false);
		block = block->next;
	}
	return (true);
}

int	handle_redirect(t_all *shell)
{
	t_input	*current;

	current = shell->cmd_line;
	handle_heredoc(shell);
	handle_block(current);
	while (current)
	{
		if (current->token == PIPE)
			handle_block(current->next);
		current = current->next;
	}
	return (1);
}
