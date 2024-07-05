/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:02:51 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 19:02:54 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*pwd;

	g_status_code = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf(2, "minishell: pwd: working directory not found\n");
		g_status_code = 1;
		return ;
	}
	ft_printf(1, "%s\n", pwd);
	free(pwd);
}
