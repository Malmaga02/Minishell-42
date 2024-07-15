/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:32:15 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/14 19:11:26 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

int	main(int ac, char **av, char **envp)
{
	t_all		all_info;
	char		*line;

	line = NULL;
	all_info = (t_all){0};
	(void)ac;
	(void)av;
	while (42)
	{
		g_status_code = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishello >: ");
		if (!line)
		{
			free_all(&all_info);
			ft_printf(2, "exit\n");
			break ;
		}
		if (all_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		all_info = get_input_complete(all_info, line, envp);
		if (!all_info.cmd_line)
			break ;
		exec_main(&all_info);
		set_clear_all(&all_info);
	}
	rl_clear_history();
	return (0);
}

// testing parsing

/* char *enum_to_str(int enume)
{
	if (enume == CMD)
		return (ft_strdup("command"));
	else if (enume == ARG)
		return (ft_strdup("argument"));
	else if (enume == FILE_W)
		return (ft_strdup("file"));
	else if (enume == EOF_DEL)
		return (ft_strdup("heredoc_del"));
	else if (enume == WORDS)
		return (ft_strdup("word"));
	else if (enume == DOLLAR_SIGN)
		return (ft_strdup("dollar sign"));
	else if (enume == PIPE)
		return (ft_strdup("pipe"));
	else if (enume == R_INPUT)
		return (ft_strdup("red. input"));
	else if (enume == R_OUTPUT)
		return (ft_strdup("red. output"));
	else if (enume == D_RED_INPUT)
		return (ft_strdup("d. red. input"));
	else if (enume == D_RED_OUTPUT)
		return (ft_strdup("d. red. output"));
	else if (enume == D_QUOTE)
		return (ft_strdup("double quote"));
	else if (enume == S_QUOTE)
		return (ft_strdup("single quote"));
	return (NULL);
} */

/*
int	main(int ac, char **av, char **envp)
{
	t_all		all_info;
	char		*line;
	int			i;

	line = NULL;
	i = 0;
	all_info = (t_all){0};
	(void)ac;
	(void)av;
	while (42)
	{
		line = readline("minishello > ");
		if (line == NULL)
		{
			perror("Error on readline");
			continue ;
		}
		all_info = get_input_complete(all_info, line, envp);
		while (all_info.cmd_line)
		{
			printf("[%s] is a %s\n", all_info.cmd_line->content, enum_to_str(all_info.cmd_line->token));
			i = 0;
			print_mtx(all_info.cmd_line->args);
			all_info.cmd_line = all_info.cmd_line->next;
		}
	}
	return (0);
} */