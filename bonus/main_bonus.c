/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:27:29 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:27:31 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_mlx(t_info *info)
{
	info->mlx = mlx_init();
	info->window = mlx_new_window(info->mlx, W, H, "miniRT_Bonus");
	info->image.img = mlx_new_image(info->mlx, W, H);
	info->image.addr = mlx_get_data_addr(info->image.img, \
		&info->image.bits_per_pixel, \
		&info->image.line_length, &info->image.endian);
	info->scene->image = &info->image;
	draw(info->scene);
	mlx_put_image_to_window(info->mlx, info->window, info->image.img, 0, 0);
	esc_and_x_hook(info);
	mlx_loop(info->mlx);
}

void	rt(const char *filename)
{
	t_info	info;

	info.scene = parse((char *)filename);
	info.scene->camera = set_up_camera(info.scene->camera);
	init_mlx(&info);
}

int	main(int ac, char const **av)
{
	if (ac == 2)
		rt(av[1]);
	else
	{
		printf("Error : \n ./rt [filename].rt");
		return (1);
	}
	return (0);
}
