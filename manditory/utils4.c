/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:24:39 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 20:47:05 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_to_objs_list(t_object **head, t_object *new)
{
	t_object	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_object	*new_object(t_otype type, void *ptr)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	new->type = type;
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}
