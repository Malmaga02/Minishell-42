/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:38:02 by lotrapan          #+#    #+#             */
/*   Updated: 2024/06/17 18:58:26 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_list(t_list *envp)
{
	t_list	*tmp;

	tmp = envp;
	if (!tmp->content)
	{
		printf("aaaaaaa\n");
		return ;
	}
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
}

void	cleanup(t_all *shell)
{
	clear_list(shell->envp);
}
