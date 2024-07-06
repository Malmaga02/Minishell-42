/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:28 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/05 19:07:54 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_all *shell, t_input *cmd_line)
{
	char	*path;
	char	**cmd;
	char	**envp;

	cmd = cmd_line->args;
	envp = lst_to_mtx(shell->envp);
	path = get_path(shell, cmd[0]);
	if ((!path) || (execve(path, cmd, envp) == -1))
	{
		printf("%s: command not found\n", cmd[0]);
		free_all(shell);
		free_mtx(envp);
		exit(127);
	}
}

void	child_exe(t_all *shell)
{
	if (is_builtin(shell)) 
	{
    	exec_builtin(shell);
    	exit(g_status_code);
	}
    else
    	exec_command(shell, shell->cmd_line);
}

void	child_init(t_all *shell, int i, int cmd_num)
{
	if (i > 0)
	{
        if (dup2(shell->pipes[i - 1][0], STDIN_FILENO) == -1)
		{
            ft_printf(2, "Error: dup2\n");
            exit(1);
        }
    }
    if (cmd_num > 1)
	{
        if (dup2(shell->pipes[i][1], STDOUT_FILENO) == -1)
		{
            ft_printf(2, "Error: dup2\n");
            exit(1);
     	}
	}
    close_pipes(shell);
	free_pipes(shell);
}

void exec_main(t_all *shell) 
{
    int 	i;
    int 	cmd_num;
    pid_t 	pid;
	t_input	*current;

	i = 0;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	current = shell->cmd_line;
    cmd_num = count_commands(current);
	if (!handle_redirect(shell, true))
		return ;
	shell = init_pipe(shell, cmd_num);
    while (current)
	{
		if (cmd_num < 1)
			break ;
		while (current && current->token != CMD)
			current = current->next;
        pid = fork();
        if (pid == -1) 
		{
            ft_printf(2, "Error: fork\n");
            exit(1);
        } 
        if (pid == 0)
		{
			child_init(shell, i, cmd_num);
			child_exe(shell);
        }
        current = current->next;
		cmd_num--;
        i++;
    }
	close_pipes(shell);
	wait_cmd(cmd_num);
	free_pipes(shell);
	return ;
}

