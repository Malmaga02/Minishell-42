/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:07 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/04 21:26:05 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_word_in_env(t_list *envp, char *word)
{
	char *str;

	while (envp)
	{
		str = (char *)envp->content;
		if (ft_strncmp(str, word, ft_strlen(word)) == 0)
			return (str + ft_strlen(word));
		envp = envp->next;
	}
	return (NULL);
}

char	*get_path(t_all *shell, char *cmd)
{
	char	*path;
	char	*part_path;
	char	*path_env;
	int		i;
	char	**possible_paths;

	i = 0;
	path_env = find_word_in_env(shell->envp, "PATH");
	if (!path_env)
		return (NULL);
	possible_paths = ft_split(path_env, ':'); 
	if (!possible_paths)
		return (NULL);
	while (possible_paths[i])
	{
		part_path = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0) // contolla se esiste e se e' eseguibile 
			return (path);
		free(path);
		i++;
	}
	free_mtx(possible_paths);
	return (NULL);
}

void	exec_builtin(t_all *shell)
{
	if (ft_strcmp(shell->cmd_line->content, "exit") == 0)
		builtin_exit(shell, shell->cmd_line);
	if (ft_strcmp(shell->cmd_line->content, "echo") == 0)
		builtin_echo(shell->cmd_line);
	if (ft_strcmp(shell->cmd_line->content, "env") == 0)
		builtin_env(shell);
	if (ft_strcmp(shell->cmd_line->content, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(shell->cmd_line->content, "cd") == 0)
		builtin_cd(shell, shell->cmd_line);
	if (ft_strcmp(shell->cmd_line->content, "unset") == 0)
		builtin_unset(shell->cmd_line, shell->envp);
	if (ft_strcmp(shell->cmd_line->content, "export") == 0)
		builtin_export(shell);
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
