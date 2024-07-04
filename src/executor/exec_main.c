/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:28 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/04 21:29:30 by lotrapan         ###   ########.fr       */
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

int exec_main(t_all *shell) 
{
    int 	i;
    int 	cdm_num;
    pid_t 	pid;

	i = 0;
    cdm_num = count_commands(shell->cmd_line);
	//handle_redirect (in caso di errore return)
	shell = init_pipe(shell, cdm_num);
    while (shell->cmd_line)
	{
		if (cdm_num < 1)
			break ;
		while (shell->cmd_line && shell->cmd_line->token != CMD)
			shell->cmd_line = shell->cmd_line->next;
        pid = fork();
        if (pid == -1) 
		{
            ft_printf(2, "Error: fork\n");
            exit(1);
        }
        if (pid == 0) //child
		{
            if (i > 0) // input
			{
                if (dup2(shell->pipes[i - 1][0], STDIN_FILENO) == -1)
				{
                    ft_printf(2, "Error: dup2\n");
                    exit(1);
                }
            }
            if (cdm_num > 1) //output
			{
               	if (dup2(shell->pipes[i][1], STDOUT_FILENO) == -1)
				{
               	    ft_printf(2, "Error: dup2\n");
               	    exit(1);
               	}
			}
			else
				//ultimo_cmd
            close_pipes(shell);
			free_pipes(shell);
            if (is_builtin(shell)) 
			{
                exec_builtin(shell);
                exit(0);//variabile globale
			}
            else
            	exec_command(shell, shell->cmd_line);
        }
        shell->cmd_line = shell->cmd_line->next;
		cdm_num--;
        i++;
    }
	close_pipes(shell);
	i = 0;
    while (i < cdm_num)
	{
		wait(NULL);
		i++;
	}
	free_pipes(shell);
	return (1);
}

