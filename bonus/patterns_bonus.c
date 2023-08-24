/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:28:03 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:28:07 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_v3	sphere_pattern(t_sphere *s, t_interesect *in)
{
	t_uv	uv;
	int		x;
	int		y;

	uv = sphere_uv(s, in);
	x = (int)(uv.u * 16);
	y = (int)(uv.v * 8);
	if ((x + y) % 2 == 0)
		return (s->color);
	else
		return (s->color2);
}

t_v3	plane_pattern(t_plane *p, t_interesect *in)
{
	double	scale;

	scale = 0.1;
	if ((int)((floor(in->hit_point.x * scale + BIAS) \
				+ floor(in->hit_point.y * scale + BIAS) \
				+ floor(in->hit_point.z * scale + BIAS))) % 2 == 0)
		return (p->color);
	else
		return (p->color2);
}

t_v3	cylinder_pattern(t_cylinder *c, t_interesect *in)
{
	double	scale;

	scale = 0.3;
	if ((int)((floor(in->hit_point.x * scale) \
				+ floor(in->hit_point.y * scale))) % 2 == 0)
		return (c->color);
	else
		return (c->color2);
}

t_v3	cone_pattern(t_cone *c, t_interesect *in)
{
	double	scale;

	scale = 0.3;
	if ((int)((floor(in->hit_point.x * scale + BIAS) \
					+ floor(in->hit_point.y * scale + BIAS))) % 2 == 0)
		return (c->color);
	else
		return (c->color2);
}

t_v3	get_pattern(t_interesect *in)
{
	if (in->type == SPHERE)
		return (sphere_pattern((t_sphere *)in->shape, in));
	else if (in->type == CYLINDER)
		return (cylinder_pattern((t_cylinder *)in->shape, in));
	else if (in->type == PLANE)
		return (plane_pattern((t_plane *)in->shape, in));
	else if (in->type == CONE)
		return (cone_pattern((t_cone *)in->shape, in));
	return ((t_v3){0, 0, 0});
}
