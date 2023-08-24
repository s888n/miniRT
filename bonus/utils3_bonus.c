/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:29:17 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 21:29:18 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	parse_error(char *msg, int en)
{
	printf("%s \nError : %s %s \n", RED, msg, RESET);
	exit (en);
}

void	norm_victor(t_v3 *v)
{
	double	len;

	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

int	valid_color(t_v3 color)
{
	if (color.x < 0 || color.x > 1 || \
		color.y < 0 || color.y > 1 || \
		color.z < 0 || color.z > 1)
		return (0);
	return (1);
}

void	spacer(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\b' || s[i] == '\t' || \
			s[i] == '\n' || s[i] == '\v' || s[i] == '\f')
			s[i] = ' ';
}

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
