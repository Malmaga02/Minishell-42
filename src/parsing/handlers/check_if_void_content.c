#include "minishell.h"

t_input	*organize_void_token(t_input *cmdline)
{
	t_input	*tmp;
	int		cmd_flag;
	int		new_token;

	tmp = cmdline;
	while (tmp)
	{
		if (tmp->token == CMD)
			cmd_flag = 1;
		if (find_token_type(tmp->token) == OPERATORS)
			cmd_flag = 0;
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
	return (cmdline);
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
		if (cmdline->content && !cmdline->content[0])
			cmdline->token = VOID;
		cmdline = cmdline->next;
	}
	all_info.cmd_line = organize_void_token(all_info.cmd_line);
	return (all_info);
}
