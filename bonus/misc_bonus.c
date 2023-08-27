/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:27:47 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/27 14:07:20 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	close_window(t_info *info)
{
	mlx_destroy_image(info->mlx, info->image.img);
	mlx_destroy_window(info->mlx, info->window);
	free_scene(info->scene);
	exit (0);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == 53)
		close_window(info);
	return (0);
}

int	esc_and_x_hook(t_info *info)
{
	mlx_hook(info->window, 17, 0, close_window, info);
	mlx_hook(info->window, 2, 0, key_press, info);
	return (0);
}

int	invalid_double(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != '.' && \
		(s[i] == '-' && i != 0))
			return (1);
	return (0);
}

int	check_double(char *s, int n)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == '.')
			count++;
	if (count > n || invalid_double(s))
		return (0);
	return (1);
}
