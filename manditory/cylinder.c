/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:01:59 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 16:23:00 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	cylinder_intersection(t_ray *r, t_cylinder *cy)
{
	t_abc	x;
	t_v3	oc;

	oc = minus_vectors(r->origin, cy->p);
	x.a = dot(r->direction, r->direction) - \
		pow(dot(r->direction, cy->normal), 2);
	x.b = 2 * (dot(oc, r->direction) - \
			(dot(oc, cy->normal) * dot(r->direction, cy->normal)));
	x.c = dot(oc, oc) - pow(dot(oc, cy->normal), 2) - pow(cy->radius, 2);
	x.delta = pow(x.b, 2) - (4 * x.a * x.c);
	if (x.delta < 0)
		return (-1);
	x.t1 = (-(x.b) - sqrt(x.delta)) / (2 * x.a);
	x.t2 = (-(x.b) + sqrt(x.delta)) / (2 * x.a);
	if (x.t1 < 0 && x.t2 < 0)
		return (-1);
	if (x.t1 < 0)
		return (x.t2);
	if (x.t2 < 0)
		return (x.t1);
	return (fmin(x.t1, x.t2));
	return (-1);
}

t_interesect	cy_top_cap(t_ray *r, t_cylinder *c, t_interesect in)
{
	t_interesect	i;
	t_plane			p;
	t_v3			cp;

	p.normal = c->normal;
	p.p0 = c->top_cap_center;
	i.t = plane_intersection(r, &p);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		cp = minus_vectors(add_vectors(r->origin, \
				multi_vec_by_n(r->direction, i.t)), c->top_cap_center);
		if (dot(cp, cp) <= c->radius * c->radius)
		{
			i.color = c->color;
			i.hit_point = add_vectors(r->origin, \
				multi_vec_by_n(r->direction, i.t));
			i.normal = p.normal;
			in = i;
		}
	}
	return (in);
}

t_interesect	cy_btm_cap(t_ray *r, t_cylinder *c, t_interesect in)
{
	t_interesect	i;
	t_v3			cp;
	t_plane			p;

	p.normal = multi_vec_by_n(c->normal, -1);
	p.p0 = c->bottom_cap_center;
	i.t = plane_intersection(r, &p);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		cp = minus_vectors(add_vectors(r->origin, \
			multi_vec_by_n(r->direction, i.t)), c->bottom_cap_center);
		if (dot(cp, cp) <= c->radius * c->radius)
		{
			i.color = c->color;
			i.hit_point = add_vectors(r->origin, \
				multi_vec_by_n(r->direction, i.t));
			i.normal = p.normal;
			in = i;
		}
	}
	return (in);
}

t_interesect	cylinder(t_ray *r, t_cylinder *c, t_interesect in)
{
	t_interesect	i;
	double			d;

	i.t = cylinder_intersection(r, c);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		i.color = c->color;
		i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
		d = dot(c->normal, minus_vectors(i.hit_point, c->bottom_cap_center));
		if (d < 0 || d > c->height)
			return (in);
		i.normal = normalize(minus_vectors(minus_vectors(i.hit_point, \
				c->p), multi_vec_by_n(c->normal, \
				dot(minus_vectors(i.hit_point, c->p), c->normal))));
		in = i;
	}
	return (in);
}

t_interesect	get_cylinder(t_ray *r, t_cylinder *c, t_interesect in)
{
	t_interesect	i;
	t_interesect	top;
	t_interesect	btm;

	i = cylinder(r, c, in);
	top = cy_top_cap(r, c, in);
	btm = cy_btm_cap(r, c, in);
	return (min_positive_in(i, top, btm));
}
