/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_input_addback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:28:00 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 12:28:07 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dll_input_addback(t_input **lst, t_input *new)
{
	t_input	*last;

	if (!lst || !new)
		return ;
	last = dll_input_last(*lst);
	if (!(*lst))
	{
		new->prev = NULL;
		new->next = NULL;
		*lst = new;
		return ;
	}
	new->prev = last;
	new->next = NULL;
	last->next = new;
}
