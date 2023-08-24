/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:29:28 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 17:37:56 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_v3	divide_vec_by_n(t_v3 vec, double n)
{
	vec.x *= 1 / n;
	vec.y *= 1 / n;
	vec.z *= 1 / n;
	return (vec);
}

double	dot(t_v3 vec1, t_v3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_v3	cross(t_v3 v1, t_v3 v2)
{
	return ((t_v3){v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x});
}

t_v3	normalize(t_v3 vec)
{
	double	len;

	len = vec_len(vec);
	if (len == 0)
	{
		printf ("Error\n:Devider is 0");
		exit (0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_v3	multi_vec_by_n(t_v3 vec, double n)
{
	vec.x *= n;
	vec.y *= n;
	vec.z *= n;
	return (vec);
}
