/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:36 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 20:02:37 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	plane_intersection(t_ray *r, t_plane *p)
{
	t_v3	n;
	t_v3	c;
	double	t;
	double	d;
	double	a;

	c = minus_vectors(r->origin, p->p0);
	n = normalize(p->normal);
	t = dot(r->direction, n);
	if (t != 0)
	{
		d = dot(c, n);
		a = -d / t;
		if (a < 0.000001)
			return (-1);
		return (a);
	}
	return (-1.0);
}

t_interesect	get_plane(t_ray *r, t_plane *p, t_interesect in)
{
	t_interesect	i;

	i.t = plane_intersection(r, p);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		i.hit_point = add_vectors(r->origin, \
			multi_vec_by_n(r->direction, i.t));
		i.color = p->color;
		i.normal = p->normal;
		if (dot(i.normal, r->direction) > 0)
			i.normal = multi_vec_by_n(i.normal, -1);
		in = i;
	}
	return (in);
}
