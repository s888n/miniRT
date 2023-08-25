/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:00:27 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/25 23:45:32 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_v3	int_to_rgb(int color)
{
	t_v3	rgb;

	rgb.x = ((color & 0xFF0000) >> 16) / 255.0;
	rgb.y = ((color & 0x00FF00) >> 8) / 255.0;
	rgb.z = ((color & 0x0000FF)) / 255.0;
	return (rgb);
}

int	clamp_uv(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

t_texture	load_texture(char *path)
{
	t_texture	t;

	if (ft_strncmp(path + (ft_strlen2(path) - 4), ".xpm", 4))
		parse_error("error : invalid texture file\n", 1);
	if (!check_file(path))
		parse_error("error : texture file error!\n", 23);
	t.mlx = mlx_init();
	t.img = mlx_xpm_file_to_image(t.mlx, path, \
			&t.width, &t.height);
	if (!t.img)
		parse_error("error : couldn't load texture\n", 1);
	t.addr = mlx_get_data_addr(t.img, &t.bits_per_pixel, \
			&t.line_length, &t.endian);
	return (t);
}

t_v3	get_bump(t_texture *t, t_uv uv)
{
	int		u;
	int		v;
	int		color;
	t_v3	bump;

	u = floor((uv.u) * t->width);
	v = floor((uv.v) * t->height);
	u = clamp_uv(u, 0, t->width - 1);
	v = clamp_uv(v, 0, t->height - 1); 
	color = *(unsigned int *)(t->addr + \
			(v * t->line_length + u * (t->bits_per_pixel / 8)));
	bump = int_to_rgb(color);
	return (bump);
}
