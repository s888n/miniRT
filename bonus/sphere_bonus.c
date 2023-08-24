/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:28:41 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 20:27:34 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	sphere_intersection(t_ray *r, t_sphere *s)
{
	t_abc	x;
	t_v3	oc;

	oc = minus_vectors(r->origin, s->center);
	x.a = dot(r->direction, r->direction);
	x.b = 2 * dot(oc, r->direction);
	x.c = dot(oc, oc) - pow(s->radius, 2);
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
}

t_interesect	get_sphere(t_ray *r, t_sphere *s, t_interesect in)
{
	t_interesect	i;

	i.t = sphere_intersection(r, s);
	if (i.t > 0 && (in.t < 0 || i.t < in.t))
	{
		i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
		if (s->has_bump == 1)
		{
			i.color = get_bump(&s->bump, sphere_uv(s, &i));
			i.normal = normalize(get_bump(&s->bump, sphere_uv(s, &i)));
		}
		else
		{
			i.normal = normalize(minus_vectors(i.hit_point, s->center));
			i.color = s->color;
		}
		i.shape = s;
		i.type = SPHERE;
		i.has_pattern = s->has_pattern;
		in = i;
	}
	return (in);
}
