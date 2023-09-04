/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_cam_lght.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:01:19 by srachdi           #+#    #+#             */
/*   Updated: 2023/09/04 18:49:31 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_color(t_v3 *clr, char *field)
{
	char	**color;
	int		i;

	i = 0;
	color = ft_split(field, ',');
	if (arrlen(color) != 3)
		parse_error("R,G,B\n", 7);
	if (!check_double(color[0], 1) || !check_double(color[1], 1) || \
		!check_double(color[2], 1))
		parse_error("nice try  :)\n", 7);
	clr->x = ft_atod(color[0]) / 255.0;
	clr->y = ft_atod(color[1]) / 255.0;
	clr->z = ft_atod(color[2]) / 255.0;
	free_arr(color);
}

void	parse_coords(t_v3 *point, char *field)
{
	char	**coords;

	coords = ft_split(field, ',');
	if (arrlen(coords) != 3)
		parse_error("parse_coords : too few or too many args\n", 10);
	if (!check_double(coords[0], 1) || \
		!check_double(coords[1], 1) || !check_double(coords[2], 1))
		parse_error ("nice try  :)\n", 7);
	point->x = ft_atod(coords[0]);
	point->y = ft_atod(coords[1]);
	point->z = ft_atod(coords[2]);
	free_arr (coords);
}

void	ambient(t_scene *scene, char **arr)
{
	if (scene->ambient_color.x != -1)
		parse_error(" you can only change once per scene\n", 4);
	if (arrlen(arr) != 3)
		parse_error("usage : A   ratio   R,G,B\n", 5);
	invalid_shape(arr[0], 1);
	if(!check_double(arr[1], 1))
		parse_error("nice try  :)\n", 7);
	scene->ambient_intensity = ft_atod(arr[1]);
	if (scene->ambient_intensity < 0 || scene->ambient_intensity > 1)
		parse_error("ratio is too high or too low or you're too high !!\n", 6);
	parse_color(&scene->ambient_color, arr[2]);
	if (!valid_color(scene->ambient_color))
		parse_error("color not valid\n", 8);
	free_arr(arr);
}

void	camera(t_scene *scene, char **arr)
{
	t_camera	*cam;

	if (arrlen(arr) != 4)
		parse_error("usage : C   x,y,z   a,b,c   fov", 9);
	invalid_shape(arr[0], 1);
	cam = malloc(sizeof(t_camera));
	parse_coords(&cam->origin, arr[1]);
	parse_coords(&cam->forward, arr[2]);
	if(!check_double(arr[3], 1))
		parse_error("nice try  :)\n", 7);
	cam->fov = ft_atod(arr[3]);
	if (cam->fov < 0 || cam->fov > 180)
		parse("fov must be in this range =>[0, 180]\n");
	scene->camera = cam;
	free_arr(arr);
}

void	light(t_scene *scene, char **arr)
{
	t_light	*light;

	if (arrlen(arr) != 4)
		parse_error("usage : L   x,y,z   brightness    R,G,B\n", 11);
	invalid_shape(arr[0], 1);
	light = malloc(sizeof(t_light));
	parse_coords(&light->p0, arr[1]);
	if(!check_double(arr[2], 1))
		parse_error("nice try  :)\n", 7);
	light->intensity = ft_atod(arr[2]);
	if (light->intensity < 0 || light->intensity > 1)
		parse_error("brightness must be in this range =>[0, 1]\n", 12);
	parse_color(&light->color, arr[3]);
	if (!valid_color(light->color))
		parse_error("color not valid\n", 12);
	scene->light = light;
	free_arr(arr);
}
