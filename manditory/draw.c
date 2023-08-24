/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:01 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 16:30:35 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	draw(t_scene *scene)
{
	t_v3	color;
	t_ray	r;

	scene->j = H - 1;
	while (scene->j >= 0)
	{
		scene->i = W - 1;
		while (scene->i >= 0)
		{
			scene->u = (double)scene->i / (double)(W - 1);
			scene->v = (double)scene->j / (double)(H - 1);
			r = calculate_ray(scene->camera, scene->u, scene->v);
			color = get_color(&r, scene);
			put_pixel(scene->image, \
					W - scene->i - 1, H - scene->j - 1, rgb_to_int(&color));
			scene->i--;
		}
		scene->j--;
	}
}
