#include "minishell.h"

void	free_parsing(t_parsing *parsing)
{
	free(parsing->arr_token);
	parsing->arr_token = NULL;
	free_mtx(parsing->mtx_from_input);
	parsing->mtx_from_input = NULL;
	free(parsing->input);
	parsing->input = NULL;
	free(parsing);
	parsing = NULL;
}

void	set_clear_all(t_all *all)
{
	dll_input_clear(&(all->cmd_line));
	all->cmd_line = NULL;
	close_pipes(all);
	free_pipes(all);
	close_exec_fd();
}

void	free_all(t_all *all)
{
	ft_lstclear(&(all->envp), free);
	all->envp = NULL;
	dll_input_clear(&(all->cmd_line));
	all->cmd_line = NULL;
	close_pipes(all);
	free_pipes(all);
	close_exec_fd();
}

void	close_all(t_all *all)
{
	free_all(all);
	all = NULL;
	exit(0);
}