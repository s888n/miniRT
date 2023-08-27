/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:30:00 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/27 13:43:05 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_interesect	min_positive_in(t_interesect i1, \
		t_interesect i2, t_interesect i3)
{
	t_interesect	i;

	i.t = -1;
	if (i1.t > 0 && (i.t < 0 || i1.t < i.t))
		i = i1;
	if (i2.t > 0 && (i.t < 0 || i2.t < i.t))
		i = i2;
	if (i3.t > 0 && (i.t < 0 || i3.t < i.t))
		i = i3;
	return (i);
}

int	color_or_texture(char *s)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (arrlen(arr) == 3)
	{
		free_arr(arr);
		return (1);
	}
	if (arrlen(arr) == 1)
	{
		free_arr(arr);
		return (2);
	}
	free_arr (arr);
	return (0);
}

void	cn_patt(t_cone *cone, char *arr)
{
	cone->has_pattern = 1;
	parse_color(&cone->color2, arr);
	if (!valid_color(cone->color2))
		parse_error ("cone : invalid color\n", 16);
}

void	cy_patt(t_cylinder *cylinder, char *arr)
{
	cylinder->has_pattern = 1;
	parse_color(&cylinder->color2, arr);
	if (!valid_color(cylinder->color2))
		parse_error("cylinder : invalid color\n", 16);
}

void	invalid_shape(char *s, size_t n)
{
	if (ft_strlen2(s) != n)
		parse_error("invalid name\n", 13);
}
