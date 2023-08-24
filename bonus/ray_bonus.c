/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:28:22 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:28:23 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_ray	calculate_ray(t_camera *c, double u, double v)
{
	t_ray	r;

	r.origin = c->origin;
	r.direction = normalize(minus_vectors(add_vectors(add_vectors(c->btm_lft, \
						multi_vec_by_n(c->horizontal, u)), \
					multi_vec_by_n (c->vertical, v)), c->origin));
	return (r);
}
