/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:07 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/24 15:41:10 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_all *shell, t_input *current)
{
	t_input	*cmd;

	cmd = find_cmd_in_block(current);
	if (!cmd)
		return ;
	if (ft_strcmp(cmd->content, "exit") == 0)
		builtin_exit(shell, cmd->args);
	if (ft_strcmp(cmd->content, "echo") == 0)
		builtin_echo(cmd->args);
	if (ft_strcmp(cmd->content, "env") == 0)
		builtin_env(shell);
	if (ft_strcmp(cmd->content, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(cmd->content, "cd") == 0)
		builtin_cd(shell, cmd->args);
	if (ft_strcmp(cmd->content, "unset") == 0)
		builtin_unset(cmd->args, shell->envp);
	if (ft_strcmp(cmd->content, "export") == 0)
		builtin_export(shell, cmd->args);
	dup2(shell->std_fd_in, STDIN_FILENO);
	dup2(shell->std_fd_out, STDOUT_FILENO);
}

bool	is_builtin(t_input *current)
{
	t_input	*cmd;

	cmd = find_cmd_in_block(current);
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd->content, "exit") == 0)
		return (true);
	if (ft_strcmp(cmd->content, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->content, "env") == 0)
		return (true);
	if (ft_strcmp(cmd->content, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->content, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->content, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->content, "export") == 0)
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

t_all	*create_pipe(t_all *shell, int pipe_num)
{
	int	i;

	i = 0;
	if (pipe_num == 0)
	{
		shell->pipes = NULL;
		return (shell);
	}
	shell->pipes = ft_calloc(pipe_num + 1, sizeof(int *));
	while (i < pipe_num)
	{
		shell->pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(shell->pipes[i]) == -1)
		{
			ft_printf(2, "Error: pipe\n");
			exit(1);
		}
		i++;
	}
	return (shell);
}

void	finish_exec(t_all *shell)
{
	close_pipes(shell);
	while (wait(&g_status_code) != -1)
	{
		if (WIFEXITED(g_status_code))
			g_status_code = WEXITSTATUS(g_status_code);
		else if (WIFSIGNALED(g_status_code))
			handle_signal_child(WTERMSIG(g_status_code));
	}
	free_pipes(shell);
	dup2(shell->std_fd_in, STDIN_FILENO);
	dup2(shell->std_fd_out, STDOUT_FILENO);
	close(shell->std_fd_in);
	close(shell->std_fd_out);
	close_exec_fd();
}
