/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:25:51 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:25:52 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	clamp(double c)
{
	int	clr;

	clr = (int)(c * 255);
	if (clr > 255)
		clr = 255;
	if (clr < 0)
		clr = 0;
	return (clr);
}

int	rgb_to_int(t_v3 *color)
{
	int	c;

	c = 0;
	c |= clamp(color->x) << 16;
	c |= clamp(color->y) << 8;
	c |= clamp(color->z);
	return (c);
}

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + \
			x * (image->bits_per_pixel / 8));
	*(int *)dst = color;
}
