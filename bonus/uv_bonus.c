/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:29:20 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:29:21 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_uv	sphere_uv(t_sphere *s, t_interesect *i)
{
	t_uv	uv;
	double	theta;
	double	phi;
	double	raw_u;

	(void)s;
	uv.u = 0;
	uv.v = 0;
	theta = atan2(i->hit_point.x, i->hit_point.z);
	phi = acos(i->hit_point.y / s->radius);
	raw_u = theta / (2.0 * M_PI);
	uv.u = 1.0 - (raw_u + 0.5);
	uv.v = 1.0 - phi / M_PI;
	return (uv);
}
