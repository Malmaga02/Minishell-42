/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_input_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:28:00 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 12:28:07 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dll_input_clear(t_input **lst)
{
	t_input	*ptr;

	while (lst && *lst)
	{
		ptr = (*lst)->next;
		free((*lst)->content);
		free((*lst)->args);
		free(*lst);
		*lst = ptr;
	}
	*lst = NULL;
}
