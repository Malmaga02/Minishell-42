#include "minishell.h"

void	free_parsing(t_parsing *parsing)
{
	if (parsing && parsing->arr_token)
	{
		free(parsing->arr_token);
		parsing->arr_token = NULL;
	}
	if (parsing && parsing->mtx_from_input)
	{
		free_mtx(parsing->mtx_from_input);
		parsing->mtx_from_input = NULL;
	}
	if (parsing && parsing->input)
	{
		free(parsing->input);
		parsing->input = NULL;
	}
	if (parsing)
	{
		free(parsing);
		parsing = NULL;
	}
}

void	set_clear_all(t_all *all)
{
	if (all && all->cmd_line)
	{
		dll_input_clear(&(all->cmd_line));
		all->cmd_line = NULL;
	}
	if (all && all->pipes)
	{
		close_pipes(all);
		free_pipes(all);
	}
	close_exec_fd();
}

void	free_all(t_all *all)
{
	if (all->envp)
	{
		ft_lstclear(&(all->envp), free);
		all->envp = NULL;
	}
	if (all->cmd_line)
	{
		printf("free_all: freeing cmd_line\n");
		dll_input_clear(&(all->cmd_line));
		all->cmd_line = NULL;
	}
	if (all->pipes)
	{
		close_pipes(all);
		free_pipes(all);
	}
	close_exec_fd();
}

void	close_all(t_all *all)
{
	if (all)
	{
		free_all(all);
		all = NULL;
	}
	exit(0);
}