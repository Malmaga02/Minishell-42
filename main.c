/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:32:15 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/19 14:51:30 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;


void print_mtx(char **mtx)
{
	int	i;

	i = 0;
	printf("print_mtx\n");
	while (mtx && mtx[i])
	{
		ft_printf(1, "mtx[%d]: %s\n", i, mtx[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_all		all_info;
	char		*line;

	line = NULL;
	all_info = (t_all){0};
	(void)ac;
	(void)av;
	g_status_code = 0;
	while (42)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishello$: ");
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
			continue ;
		/* while (all_info.cmd_line)
		{
			if (all_info.cmd_line->token == CMD)
				print_mtx(all_info.cmd_line->args);
			printf("token: %d\n", all_info.cmd_line->token);
			all_info.cmd_line = all_info.cmd_line->next;
		} */
		exec_main(&all_info);
		set_clear_all(&all_info);
	}
	rl_clear_history();
	return (0);
}
