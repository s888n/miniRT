/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:59:33 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/26 18:00:55 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_objects(t_object *objects)
{
	t_object	*tmp;

	while (objects)
	{
		tmp = objects;
		if (objects->type == SPHERE)
			free_sphere((t_sphere *)objects->ptr);
		else if (objects->type == PLANE)
			free((t_plane *)objects->ptr);
		else if (objects->type == CYLINDER)
			free((t_cylinder *)objects->ptr);
		else if (objects->type == CONE)
			free((t_cone *)objects->ptr);
		objects = objects->next;
		free (tmp);
	}
}

void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights)
	{
		tmp = lights;
		lights = lights->next;
		free(tmp);
	}
}

void	free_scene(t_scene *scene)
{
	free_objects(scene->objects);
	free_lights(scene->lights);
	free(scene->camera);
	free(scene);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

void	free_sphere(t_sphere *sphere)
{
	if (sphere->has_bump == 1)
	{
		mlx_destroy_image (sphere->bump.mlx, sphere->bump.img);
		free (sphere->bump.mlx);
	}
	free (sphere);
}
