/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:42:54 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/16 11:35:30 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_child(int signal)
{
	if (signal == SIGINT)
		g_status_code = 130;
	if (signal == SIGQUIT)
	{
		ft_printf(2, "Quit\n");
		g_status_code = 131;
	}
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_status_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_sigint_exec(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(2, "\n");
		g_status_code = 130;
	}
}
