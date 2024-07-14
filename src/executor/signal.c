/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:42:54 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/14 19:06:23 by lotrapan         ###   ########.fr       */
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

void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_status_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_exec_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(2, "\n");
		g_status_code = 130;
	}
}