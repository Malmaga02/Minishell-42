/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_input_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:28:00 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/24 12:28:07 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*dll_input_last(t_input *lst)
{
	t_input	*new;

	if (!lst)
		return (NULL);
	new = lst;
	while (new->next != NULL)
		new = new->next;
	return (new);
}
