/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:28:57 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 20:31:41 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	allowedchars(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		ft_isdigit(c) || c == '.' || c == ',' || c == '-')
		return (1);
	return (0);
}

int	countchar(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s[++i])
		if (s[i] == c)
			count++;
	return (count);
}

int	validfilename(char *filename)
{
	if (!ft_strncmp(filename + (ft_strlen2(filename) - 3), ".rt", 3))
		return (1);
	return (0);
}

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
