/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:26:00 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 20:38:08 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_abc	cone_delta(t_ray *r, t_cone *cone)
{
	t_abc	x;
	t_v3	oc;
	double	m;

	m = pow(cone->radius, 2) / pow(cone->height, 2);
	oc = minus_vectors(r->origin, cone->center);
	x.a = dot(r->direction, r->direction) - (1 + m) * \
		pow(dot(r->direction, cone->normal), 2);
	x.b = dot(r->direction, oc) - dot(r->direction, cone->normal) * \
		dot(oc, cone->normal) * (1 + m) + m * \
		cone->height * dot(r->direction, cone->normal);
	x.c = dot(oc, oc) - pow(dot(oc, cone->normal), 2) * \
		(1 + m) - pow(cone->radius, 2) + 2 * \
		m * cone->height * dot(oc, cone->normal);
	x.delta = pow(x.b, 2) - x.a * x.c;
	return (x);
}

double	cone_intersection(t_ray *r, t_cone *cone)
{
	t_abc	x;

	x = cone_delta(r, cone);
	if (x.delta < 0)
		return (-1);
	x.t1 = (-(x.b) - sqrt(x.delta)) / x.a;
	x.t2 = (-(x.b) + sqrt(x.delta)) / x.a;
	if (x.t1 < 0 && x.t2 < 0)
		return (-1);
	if (x.t1 < 0)
		return (x.t2);
	if (x.t2 < 0)
		return (x.t1);
	return (fmin(x.t1, x.t2));
}

t_interesect	cone_base(t_ray *r, t_cone *cone, t_interesect in)
{
	t_interesect	i;
	t_plane			p;
	t_v3			cp;

	p.p0 = cone->center;
	p.normal = cone->normal;
	i.t = plane_intersection(r, &p);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		cp = minus_vectors(add_vectors(r->origin, \
				multi_vec_by_n(r->direction, i.t)), cone->center);
		if (dot(cp, cp) <= cone->radius * cone->radius)
		{
			i.color = cone->color;
			i.hit_point = add_vectors(r->origin, \
				multi_vec_by_n(r->direction, i.t));
			i.normal = p.normal;
			in = i;
		}
	}
	return (in);
}

t_interesect	cone_body(t_ray *r, t_cone *cone, t_interesect in)
{
	t_interesect	i;
	double			ph;

	i.t = cone_intersection(r, cone);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		i.color = cone->color;
		i.hit_point = add_vectors(r->origin, \
			multi_vec_by_n(r->direction, i.t));
		ph = dot(minus_vectors(i.hit_point, \
				cone->center), cone->normal);
		if (ph < 0 || ph > cone->height)
			return (in);
		i.normal = normalize(minus_vectors(add_vectors(cone->center, \
			multi_vec_by_n(cone->normal, ph)), \
			i.hit_point));
		i.type = CONE;
		i.shape = cone;
		i.has_pattern = cone->has_pattern;
		in = i;
	}
	return (in);
}

t_interesect	get_cone(t_ray *r, t_cone *cone, t_interesect in)
{
	t_interesect	i;

	i = cone_body(r, cone, in);
	i = cone_base(r, cone, i);
	return (i);
}
