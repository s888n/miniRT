/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_pl_cy_cn_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:28:30 by srachdi           #+#    #+#             */
/*   Updated: 2023/09/06 08:16:00 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	sp_tex_patt(t_sphere *sphere, char *arr)
{
	if (color_or_texture(arr) == 1)
	{
		sphere->has_pattern = 1;
		parse_color(&sphere->color2, arr);
		if (!valid_color(sphere->color2))
			parse_error("sphere ,invalid color\n", 14);
	}
	else if (color_or_texture(arr) == 2)
	{
		sphere->has_bump = 1;
		sphere->bump = load_texture(arr);
	}
	else
		parse_error("sphere : invalid color or texture\n", 14);
}

void	sp(t_scene *scene, char **arr)
{
	t_sphere	*sphere;

	if (arrlen(arr) != 4 && arrlen(arr) != 5)
		parse_error("sphere : sp     x,y,z   diameter    R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	sphere = malloc(sizeof(t_sphere));
	parse_coords(&sphere->center, arr[1]);
	if (!check_double(arr[2], 1))
		parse_error("sphere : Bruh?\n", 14);
	sphere->radius = ft_atod(arr[2]) / 2.0;
	parse_color(&sphere->color, arr[3]);
	sphere->has_pattern = 0;
	sphere->has_bump = 0;
	if (!valid_color(sphere->color))
		parse_error("sphere ,invalid color\n", 14);
	if (arrlen(arr) == 5)
		sp_tex_patt(sphere, arr[4]);
	add_to_objs_list(&scene->objects, new_object(SPHERE, sphere));
	free_arr(arr);
}

void	pl(t_scene *scene, char **arr)
{
	t_plane	*plane;

	if (arrlen(arr) != 4 && arrlen(arr) != 5)
		parse_error("plane : pl     x,y,z   a,b,c    R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	plane = malloc(sizeof(t_plane));
	parse_coords(&plane->p0, arr[1]);
	parse_coords(&plane->normal, arr[2]);
	norm_victor(&plane->normal);
	parse_color(&plane->color, arr[3]);
	plane->has_pattern = 0;
	if (!valid_color(plane->color))
		parse_error("plane : invalid color\n", 15);
	if (arrlen(arr) == 5)
	{
		parse_color(&plane->color2, arr[4]);
		plane->has_pattern = 1;
		if (!valid_color(plane->color2))
			parse_error("plane : invalid color\n", 15);
	}
	add_to_objs_list(&scene->objects, new_object(PLANE, plane));
	free_arr(arr);
}

void	cy(t_scene *scene, char **arr)
{
	t_cylinder	*cylinder;

	if (arrlen(arr) != 6 && arrlen(arr) != 7)
		parse_error("cy x,y,z a,b,c diameter height  R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	cylinder = malloc(sizeof(t_cylinder));
	parse_coords(&cylinder->p, arr[1]);
	parse_coords(&cylinder->normal, arr[2]);
	norm_victor(&cylinder->normal);
	cylinder->radius = ft_atod(arr[3]) / 2;
	cylinder->height = ft_atod(arr[4]);
	cylinder->top_cap_center = add_vectors(cylinder->p, \
		multi_vec_by_n(cylinder->normal, cylinder->height / 2));
	cylinder->bottom_cap_center = add_vectors(cylinder->p, \
		multi_vec_by_n(cylinder->normal, -1.0 * (cylinder->height / 2)));
	cylinder->has_pattern = 0;
	parse_color(&cylinder->color, arr[5]);
	if (!valid_color(cylinder->color))
		parse_error("cylinder : invalid color\n", 16);
	if (arrlen(arr) == 7)
		cy_patt(cylinder, arr[6]);
	add_to_objs_list(&scene->objects, new_object(CYLINDER, cylinder));
	free_arr(arr);
}

void	cn(t_scene *scene, char **arr)
{
	t_cone	*cone;

	if (arrlen(arr) != 6 && arrlen(arr) != 7)
		parse_error("cn  x,y,z  a,b,c   diameter  height R,G,B\n", 13);
	invalid_shape(arr[0], 2);
	cone = malloc(sizeof(t_cone));
	parse_coords(&cone->center, arr[1]);
	parse_coords(&cone->normal, arr[2]);
	norm_victor(&cone->normal);
	if (!check_double(arr[3], 1) || !check_double(arr[4], 1))
		parse_error("cone : Bruh ?\n", 16);
	cone->radius = ft_atod(arr[3]) / 2;
	cone->height = ft_atod(arr[4]);
	cone->tip = add_vectors(cone->center, \
		multi_vec_by_n(cone->normal, cone->height));
	cone->axis = minus_vectors(cone->tip, cone->center);
	cone->has_pattern = 0;
	parse_color(&cone->color, arr[5]);
	if (!valid_color(cone->color))
		parse_error("cone : invalid color\n", 16);
	if (arrlen(arr) == 7)
		cn_patt(cone, arr[6]);
	add_to_objs_list(&scene->objects, new_object(CONE, cone));
	free_arr(arr);
}
