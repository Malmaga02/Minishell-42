/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:32:15 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/26 13:39:34 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

t_all	process_line(t_all all_info, char *line, char **envp)
{
	char		*trimmed;

	
	trimmed = ft_strtrim(line, "\t \r\v");
	if (ft_strlen(trimmed) != 0)
	{
		add_history(line);
		all_info = get_input_complete(all_info, trimmed, envp);	
		free(line);
		free(trimmed);
		exec_main(&all_info);
		set_clear_all(&all_info);
	}
	else
	{
		free(line);
		free(trimmed);
	}
	return (all_info);
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
			break ;
		all_info = process_line(all_info, line, envp);
	}
	free_all(&all_info);
	ft_printf(2, "exit\n");
	rl_clear_history();
	return (0);
}
