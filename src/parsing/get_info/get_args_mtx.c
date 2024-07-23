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

int	count_args(t_input *cmdline, int token, int if_cmd_before_red)
{
	int len;

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
	{
		if (if_cmd_before_red)
		{
			while (cmdline && (cmdline->token == FILE_W || cmdline->token == ARG))
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
	}
	return (len);
}


char	**handle_args_redirects(t_input *cmdline, char **args, int if_cmd_before_red)
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
	while (cmdline)
	{
		if (if_cmd_before_red && !(cmdline->token == FILE_W || cmdline->token == ARG))
			break ;
		else if (!if_cmd_before_red && cmdline->token == CMD)
		{
			args[i] = cmdline->content;
			if (!args[i])
				return (free(args), NULL);
			break ;
		}
		args[i] = cmdline->content;
		if (!args[i])
			return (free(args), NULL);
		cmdline = cmdline->next;
		i++;
	}
	return (args);
}

char	**get_args_cmds(t_input *cmdline)
{
	int     len;
	int		i;
	char    **args;

	i = 0;
	len = count_args(cmdline, cmdline->token, 0);
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
	int     len;
	int		i;
	int     if_cmd_before_red;
	char    **args;

	i = 0;
	if_cmd_before_red = find_if_cmd_before_red(head, cmdline);
	len = count_args(cmdline, cmdline->token, if_cmd_before_red);
	args = ft_calloc(len + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args = handle_args_redirects(cmdline, args, if_cmd_before_red);
	if (!args)
		return (NULL);
	return (args);
}

t_input	*create_args_mtx(t_input *cmdline, t_input *head)
{
	cmdline->args = NULL;
	if (!(cmdline->token == CMD || check_which_operator(cmdline->token) == REDIRECTS))
		return (cmdline);
	if (cmdline->token == CMD)
		cmdline->args = get_args_cmds(cmdline);
	else if (check_which_operator(cmdline->token) == REDIRECTS)
		cmdline->args = get_args_redirects(cmdline, head);
	if (!cmdline->args)
		return (NULL);
	return (cmdline);    
}

t_input	*get_args_mtx(t_input *cmd_line)
{
	t_input *cmdline;
	t_input *current;

	current = NULL;
	cmdline = cmd_line;
	while (cmdline)
	{
		cmdline = create_args_mtx(cmdline, cmd_line);
		if (!cmdline)
			return (dll_input_clear(&cmd_line), NULL);
		cmdline = cmdline->next;
	}
	return (cmd_line);
}
