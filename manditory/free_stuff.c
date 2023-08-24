/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:04 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 20:02:05 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_objects(t_object *objects)
{
	t_object	*tmp;

	while (objects)
	{
		tmp = objects;
		if (objects->type == SPHERE)
			free((t_sphere *)objects->ptr);
		else if (objects->type == PLANE)
			free((t_plane *)objects->ptr);
		else if (objects->type == CYLINDER)
			free((t_cylinder *)objects->ptr);
		objects = objects->next;
		free (tmp);
	}
}

void	free_scene(t_scene *scene)
{
	free_objects (scene->objects);
	free (scene->light);
	free (scene->camera);
	free (scene);
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
