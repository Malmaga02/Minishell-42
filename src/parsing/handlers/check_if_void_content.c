#include "minishell.h"

t_input	*organize_void_token(t_input *cmdline)
{
	t_input	*tmp;
	int		cmd_flag;
	int		new_token;

	tmp = cmdline;
	while (tmp)
	{
		if ((!tmp->prev && tmp->next) && tmp->token == VOID)
			tmp->next->token = CMD;
		if (tmp->prev && tmp->token == VOID)
		{
			new_token = get_word_token(tmp->prev->token);
			if (new_token == -1)
				return (NULL);
			if (tmp->next && find_token_type(tmp->next->token) == WORDS)
				tmp->next->token = new_token;
		}
		tmp = tmp->next;
	}
	if (!handle_operators_error(cmdline))
		return (NULL);
	return (cmdline);
}

int	no_cmd_after_pipe(t_input *cmdline)
{
	cmdline = cmdline->next;
	while (cmdline && cmdline->token != PIPE)
	{
		if (cmdline->token == CMD)
			return (0);
		cmdline = cmdline->next;
	}
	return (1);
}

int	no_input_for_redirect(t_input *cmdline)
{
	cmdline = cmdline->next;
	while (cmdline && find_token_type(cmdline->token) != OPERATORS)
	{
		if (find_token_type(cmdline->token) == WORDS)
			return (0);
		cmdline = cmdline->next;
	}
	return (1);
}

int	handle_operators_error(t_input *cmdline)
{
	while (cmdline)
	{
		if (cmdline->token == PIPE && no_cmd_after_pipe(cmdline))
			return (ft_putendl_fd("No command found", 2), 0);
		if (find_token_type(cmdline->token) == REDIRECTS && no_input_for_redirect(cmdline))
			return (ft_putendl_fd("No command found", 2), 0);
		cmdline = cmdline->next;
	}
	return (1);
}

t_all   check_if_void_content(t_all all_info)
{
	t_input *cmdline;
	int		size;

	cmdline = all_info.cmd_line;
	size = dll_input_size(cmdline);
	if (size == 1)
	{
		if (cmdline->content && !cmdline->content[0])
			cmdline->token = VOID;
		return (all_info);
	}
	while (cmdline)
	{
		if (cmdline->token == CMD && (cmdline->next && find_token_type(cmdline->next->token) == WORDS))
		{
			if (cmdline->content && !cmdline->content[0])
			{
				cmdline->token = VOID;
				cmdline->next->token = CMD;
			}
		}
		cmdline = cmdline->next;
	}
	all_info.cmd_line = organize_void_token(all_info.cmd_line);
	return (all_info);
}
