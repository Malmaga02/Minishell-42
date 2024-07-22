/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:28 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/22 18:21:30 by lotrapan         ###   ########.fr       */
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
	if (ft_strchr(cmd_line->content, '/') != NULL)
		path = ft_strdup(cmd_line->content);
	else
		path = get_path(shell, cmd[0]);
	if ((!path) || (execve(path, cmd, envp) == -1))
	{
		ft_printf(2, "%s: command not found\n", cmd[0]);
		free(path);
		free_all(shell);
		close_exec_fd();
		free_mtx(envp);
		exit(127);
	}
}

int	count_pipe(t_input *cmd_line)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = cmd_line;
	while (tmp)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_input	*find_next_block(t_input *current)
{
	while (current)
	{
		if (current->token == PIPE)
			return (current->next);
		current = current->next;
	}
	return (NULL);
}

int	exec_init(t_all *shell, t_input *current)
{
	const int	num_pipes = count_pipe(shell->cmd_line);
	int			cmd_num;

	cmd_num = count_commands(current);
	shell->std_fd_in = dup(STDIN_FILENO);
	shell->std_fd_out = dup(STDOUT_FILENO);
	handle_redirect(shell);
	shell = create_pipe(shell, num_pipes);
	if (cmd_num == 1 && is_builtin(shell))
		return (pipe_init(shell, shell->cmd_line, 0),
			exec_builtin(shell), 0);
	return (1);
}

void	exec_main(t_all *shell)
{
	int		i;
	pid_t	pid;
	t_input	*cmd;
	t_input	*current;

	i = -1;
	if (!exec_init(shell, shell->cmd_line))
		return ;
	signal(SIGINT, handle_sigint_exec);
	current = shell->cmd_line;
	while (current && ++i > -1)
	{
		cmd = find_cmd_in_block(current);
		if (cmd)
		{
			pid = fork();
			if (pid == -1)
				exit(1);
			if (pid == 0)
				handle_child(shell, cmd, i);
		}
		current = find_next_block(current);
	}
	finish_exec(shell);
}
