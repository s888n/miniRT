/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:26:57 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:27:12 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_v3	reflect_vec(t_v3 l, t_v3 n)
{
	t_v3	r;

	r = multi_vec_by_n(n, 2 * dot(l, n));
	r = minus_vectors(r, l);
	return (r);
}

void	add_to_light_list(t_light **light, t_light *new)
{
	t_light	*tmp;

	if (!*light)
		*light = new;
	else
	{
		tmp = *light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
