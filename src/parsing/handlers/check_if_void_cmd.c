#include "minishell.h"

int	check_if_redirect_before(t_input *head, int current)
{
	int	i;

	i = 0;
	while (head && i < current)
	{
		if (check_which_operator(head->token) == REDIRECTS)
			return (1);
		head = head->next;
		i++;
	}
	return (0);
}

t_input	*organize_token(t_input *cmdline)
{
	t_input	*head;
	int		i;

	i = 0;
	head = cmdline;
	while (cmdline)
	{
		if (cmdline->token == VOID && (cmdline->next
				&& find_token_type(cmdline->next->token) == WORDS))
			cmdline->next->token = CMD;
		else if (cmdline->token == VOID
			&& check_if_redirect_before(head, i))
			return (ft_putendl_fd("Ambiguous redirect", 2), NULL);
		cmdline = cmdline->next;
		i++;
	}
	return (head);
}

t_input	*set_void_token(t_input *cmdline)
{
	t_input	*head;

	head = cmdline;
	while (cmdline)
	{
		if ((cmdline->content && !cmdline->content[0])
			&& (cmdline->token == CMD || cmdline->token == FILE_W))
			cmdline->token = VOID;
		cmdline = cmdline->next;
	}
	return (head);
}

t_all	check_if_void_cmd(t_all all_info)
{
	int		size;

	size = dll_input_size(all_info.cmd_line);
	if (size == 1)
	{
		if (all_info.cmd_line->content && !all_info.cmd_line->content[0])
			all_info.cmd_line->token = VOID;
		return (all_info);
	}
	all_info.cmd_line = set_void_token(all_info.cmd_line);
	all_info.cmd_line = organize_token(all_info.cmd_line);
	if (!all_info.cmd_line)
		return ((t_all){0});
	return (all_info);
}
