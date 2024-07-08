/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:44:34 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/08 12:02:55 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_envp(t_list **envp, char *old)
{
	char	*new;

	new = getcwd(NULL, 0);
	*envp = change_env_variable(*envp, "OLDPWD=", old);
	*envp = change_env_variable(*envp, "PWD=", new);
	return ;
}

static int	cd_home(t_all *shell, char *home_dir, char *old_pwd)
{
	if (chdir(home_dir) == 0)
		return (update_envp(&shell->envp, old_pwd), 0);
	else
	{
		g_status_code = 1;
		return (ft_printf(2, "minishell: cd: " "%s: Error home\n",
				home_dir), 1);
	}
}

int	builtin_cd(t_all *shell, t_input *cmd_line)
{
	char	*dir;
	char	*old_pwd;

	g_status_code = 0;
	dir = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!cmd_line->next)
		return (cd_home(shell, find_word_in_env(shell->envp, "HOME="),
				old_pwd));
	if (dll_input_size(cmd_line) > 2)
	{
		g_status_code = 1;
		return (ft_printf(2, "minishell: cd: too many arguments\n"), 1);
	}
	cmd_line = cmd_line->next;
	dir = cmd_line->content;
	if (chdir(dir) == 0)
		return (update_envp(&shell->envp, old_pwd), 0);
	else
	{
		g_status_code = 1;
		return (ft_printf(2, "minishell: cd: %s: No such file or directory\n",
				dir), 1);
	}
}
