/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:28 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/16 11:40:21 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_all *shell, t_input *cmd_line)
{
	char	*path;
	char	**cmd;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = cmd_line->args;
	envp = lst_to_mtx(shell->envp);
	path = get_path(shell, cmd[0]);
	if ((!path) || (execve(path, cmd, envp) == -1))
	{
		ft_printf(2, "%s: command not found\n", cmd[0]);
		free_all(shell);
		free_mtx(envp);
		exit(127);
	}
}

void	child_exe(t_all *shell, t_input *current)
{
	if (is_builtin(shell)) 
	{
    	exec_builtin(shell);
		if (shell && shell->std_fd_in > 2)
			close(shell->std_fd_in);
		if (shell && shell->std_fd_out > 2)
			close(shell->std_fd_out);
    	exit(g_status_code);
	}
    else
    	exec_command(shell, current);
}

void	pipe_init(t_all *shell, t_input *current, int i, int cmd_num)
{
	if (i > 0 && shell->pipes)
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	if (cmd_num > 1 && shell->pipes)
    	dup2(shell->pipes[i][1], STDOUT_FILENO);
	if (current->fd_in > 2)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
	}
	if (current->fd_out > 2)
	{
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
	}
	close_pipes(shell);
}

void exec_main(t_all *shell) 
{
    int 	i;
    int 	cmd_num;
    pid_t 	pid;
	t_input	*current;

	i = 0;
	current = shell->cmd_line;
    cmd_num = count_commands(current);
	shell->std_fd_in = dup(STDIN_FILENO);
	shell->std_fd_out = dup(STDOUT_FILENO);
	handle_redirect(shell);
	if (cmd_num == 1 && is_builtin(shell))
		return (pipe_init(shell, current, i, cmd_num),
			exec_builtin(shell));
	shell = init_pipe(shell, cmd_num);
	signal(SIGINT, handle_sigint_exec);
    while (current)
	{
		if (cmd_num < 1)
			break ;
		while (current && current->token != CMD)
			current = current->next;
		if (current && current->prevent)
		{	
			current = current->next;
			continue ;
		}
		if (!current)
			break ;
        pid = fork();
        if (pid == -1) 
		{
            ft_printf(2, "Error: fork\n");
            exit(1);
        } 
        if (pid == 0)
		{
			pipe_init(shell, current, i, cmd_num);
			child_exe(shell, current);
			close_exec_fd();
        }
        current = current->next;
		cmd_num--;
        i++;
    }
	close_pipes(shell);
	while (wait(&g_status_code) != -1)
	{
		if (WIFEXITED(g_status_code))
			g_status_code = WEXITSTATUS(g_status_code);
		else if (WIFSIGNALED(g_status_code))
			handle_signal_child(WTERMSIG(g_status_code));
	}
	free_pipes(shell);
}
