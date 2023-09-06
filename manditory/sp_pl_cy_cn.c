/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_pl_cy_cn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:43 by srachdi           #+#    #+#             */
/*   Updated: 2023/09/06 08:13:05 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	invalid_shape(char *s, size_t n)
{
	if (ft_strlen2(s) != n)
		parse_error("invalid name\n", 13);
}

void	sp(t_scene *scene, char **arr)
{
	t_sphere	*sphere;

	if (arrlen(arr) != 4)
		parse_error("sphere : sp     x,y,z   diameter    R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	sphere = malloc(sizeof(t_sphere));
	parse_coords(&sphere->center, arr[1]);
	if (!check_double(arr[2], 1))
		parse_error("sphere : Bruh?\n", 14);
	sphere->radius = ft_atod(arr[2]) / 2;
	parse_color(&sphere->color, arr[3]);
	if (!valid_color(sphere->color))
		parse_error("sphere ,invalid color\n", 14);
	free_arr(arr);
	add_to_objs_list(&scene->objects, new_object(SPHERE, sphere));
}

void	pl(t_scene *scene, char **arr)
{
	t_plane	*plane;

	if (arrlen(arr) != 4)
		parse_error("plane : pl     x,y,z   a,b,c    R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	plane = malloc(sizeof(t_plane));
	parse_coords(&plane->p0, arr[1]);
	parse_coords(&plane->normal, arr[2]);
	norm_victor(&plane->normal);
	parse_color(&plane->color, arr[3]);
	if (!valid_color(plane->color))
		parse_error("plane : invalid color\n", 15);
	free_arr(arr);
	add_to_objs_list(&scene->objects, new_object(PLANE, plane));
}

void	cy(t_scene *scene, char **arr)
{
	t_cylinder	*cylinder;

	if (arrlen(arr) != 6)
		parse_error("cy x,y,z a,b,c diameter height R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	cylinder = malloc(sizeof(t_cylinder));
	parse_coords(&cylinder->p, arr[1]);
	parse_coords(&cylinder->normal, arr[2]);
	norm_victor(&cylinder->normal);
	if (!check_double(arr[3], 1) || !check_double(arr[4], 1))
		parse_error("cylinder : Bruh ?\n", 16);
	cylinder->radius = ft_atod(arr[3]) / 2;
	cylinder->height = ft_atod(arr[4]);
	cylinder->top_cap_center = add_vectors(cylinder->p, \
			multi_vec_by_n(cylinder->normal, cylinder->height / 2));
	cylinder->bottom_cap_center = add_vectors(cylinder->p, \
			multi_vec_by_n(cylinder->normal, -1.0 * (cylinder->height / 2)));
	parse_color(&cylinder->color, arr[5]);
	if (!valid_color(cylinder->color))
		parse_error("cylinder : invalid color\n", 16);
	free_arr(arr);
	add_to_objs_list(&scene->objects, new_object(CYLINDER, cylinder));
}
