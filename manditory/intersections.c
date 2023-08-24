/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:10 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 20:02:11 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_interesect	get_intersection(t_ray *r, t_object *objs)
{
	t_object		*o;
	t_interesect	in;

	o = objs;
	in.t = -1;
	while (o)
	{
		if (o->type == SPHERE)
			in = get_sphere(r, (t_sphere *)o->ptr, in);
		if (o->type == PLANE)
			in = get_plane(r, (t_plane *)o->ptr, in);
		if (o->type == CYLINDER)
			in = get_cylinder(r, (t_cylinder *)o->ptr, in);
		o = o->next;
	}
	return (in);
}

t_v3	get_color(t_ray *r, t_scene *scene)
{
	t_interesect	in;
	t_v3			color;

	in = get_intersection(r, scene->objects);
	if (in.t > 0)
	{
		color = in.color;
		if (dot(in.normal, r->direction) > 0)
			in.normal = multi_vec_by_n(in.normal, -1);
		color = add_lights(color, &in, scene);
		return (color);
	}
	return (multi_vec_by_n(scene->ambient_color, scene->ambient_intensity));
}
