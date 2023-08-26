/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:16 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/26 18:29:39 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	difuse(t_interesect *in, t_light *light)
{
	t_v3	difuse;
	double	d;

	d = dot(light->direction, in->normal);
	if (d > 0)
		difuse = multi_vec_by_n(light->color, light->intensity * d * 0.5);
	else
		difuse = (t_v3){0, 0, 0};
	return (difuse);
}

t_v3	specular(t_scene *scene, t_interesect *in, t_light *light)
{
	t_v3	reflect_dir;
	t_v3	view_dir;
	double	d;

	reflect_dir = reflect_vec(light->direction, in->normal);
	view_dir = normalize(minus_vectors(scene->camera->origin, in->hit_point));
	d = pow(fmax(0.0, dot(reflect_dir, view_dir)), SHINE);
	return (multi_vec_by_n(light->color, light->intensity * d));
}

int	shade(t_interesect *in, t_scene *scene, t_light *light)
{
	t_ray			shade_ray;
	t_interesect	shade_in;

	shade_ray.origin = add_vectors(in->hit_point, \
			multi_vec_by_n(in->normal, BIAS));
	shade_ray.direction = light->direction;
	shade_in = get_intersection(&shade_ray, scene->objects);
	if (shade_in.t > 0 && \
			light->distance > vec_len(minus_vectors(in->hit_point, \
			shade_in.hit_point)) + BIAS)
		return (1);
	return (0);
}

t_v3	get_light(t_scene *s, t_light *l, t_interesect *in)
{
	t_v3	difu;
	t_v3	spec;
	t_v3	light_color;

	l->direction = normalize(minus_vectors(l->p0, in->hit_point));
	l->distance = vec_len(minus_vectors(l->p0, in->hit_point));
	difu = difuse(in, l);
	spec = specular(s, in, l);
	light_color = add_vectors(difu, spec);
	if (shade(in, s, l))
		return ((t_v3){0, 0, 0});
	else
		return (light_color);
}

t_v3	add_lights(t_v3 color, t_interesect *in, t_scene *scene)
{
	t_v3	ambiant;
	t_v3	light_color; 

	light_color = (t_v3){0, 0, 0};
	ambiant = multi_vec_by_n(scene->ambient_color, scene->ambient_intensity);
	light_color = add_vectors(get_light(scene, scene->light, in), ambiant);
	return (multi_vectors(color, light_color));
}
