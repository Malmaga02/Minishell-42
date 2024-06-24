/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:44:34 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/23 16:24:17 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_envp(t_all *shell, char *old)
{
	char	*new;

	new = getcwd(NULL, 0);
	change_env_variable(shell->envp, "PWD", new);
	change_env_variable(shell->envp, "OLD", old);
	return (0);
}

static int	cd_home(t_all *shell, char *home_dir, char *old_pwd)
{
	if (chdir(home_dir) == 0)
		return (update_envp(shell, old_pwd));
	else
		return(ft_printf(1, "minishell: cd: " "%s: Error home\n", home_dir));
}
int	builtin_cd(t_all *shell, t_input *cmd_line)
{
	char	*dir;
	char	*old_pwd;

	dir = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!cmd_line->next)
		return (cd_home(shell, find_word_in_env(shell->envp, "HOME="), old_pwd));
	if (dll_input_size(cmd_line) > 2)
		return (ft_printf(1, "minishell: cd: too many arguments\n"));
	cmd_line = cmd_line->next;
	dir = cmd_line->content;
	if (chdir(dir) == 0)
		return (update_envp(shell, old_pwd));
	else
		return(ft_printf(1, "minishell: cd: " "%s: No such file or directory\n", dir));
}
