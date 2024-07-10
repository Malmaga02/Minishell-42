/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:07 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/10 12:43:34 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_all *shell)
{
	if (ft_strcmp(shell->cmd_line->content, "exit") == 0)
		builtin_exit(shell, shell->cmd_line->args);
	if (ft_strcmp(shell->cmd_line->content, "echo") == 0)
		builtin_echo(shell->cmd_line->args);
	if (ft_strcmp(shell->cmd_line->content, "env") == 0)
		builtin_env(shell);
	if (ft_strcmp(shell->cmd_line->content, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(shell->cmd_line->content, "cd") == 0)
		builtin_cd(shell, shell->cmd_line->args);
	if (ft_strcmp(shell->cmd_line->content, "unset") == 0)
		builtin_unset(shell->cmd_line->args, shell->envp);
	if (ft_strcmp(shell->cmd_line->content, "export") == 0)
		builtin_export(shell, shell->cmd_line->args);
}

bool	is_builtin(t_all *shell)
{
	if (ft_strcmp(shell->cmd_line->content, "exit") == 0)
		return (true);
	if (ft_strcmp(shell->cmd_line->content, "echo") == 0)
		return (true);
	if (ft_strcmp(shell->cmd_line->content, "env") == 0)
		return (true);
	if (ft_strcmp(shell->cmd_line->content, "pwd") == 0)
		return (true);
	if (ft_strcmp(shell->cmd_line->content, "cd") == 0)
		return (true);
	if (ft_strcmp(shell->cmd_line->content, "unset") == 0)
		return (true);
	if (ft_strcmp(shell->cmd_line->content, "export") == 0)
		return (true);
	return (false);
}

int	count_commands(t_input *cmd_line)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = cmd_line;
	while (tmp)
	{
		if (tmp->token == CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_all	*init_pipe(t_all *shell, int cmd_num)
{
	int	i;

	i = 0;
	if (cmd_num == 1)
	{
		shell->pipes = NULL;
		return (shell);
	}
	shell->pipes = malloc(sizeof(int *) * (cmd_num - 1));
    while (i < cmd_num - 1)
	{
        shell->pipes[i] = ft_calloc(2, sizeof(int));
        if (pipe(shell->pipes[i]) == -1) {
            ft_printf(2, "Error: pipe\n");
            exit(1);
        }
		i++;
    }
	return (shell);
}

void	wait_cmd(int cmd_num)
{
	int	i;

	i = 0;
    while (i < cmd_num)
	{
		wait(NULL);
		i++;
	}
}
