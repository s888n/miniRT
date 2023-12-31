/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:13 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/23 20:02:14 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	reflect_vec(t_v3 l, t_v3 n)
{
	t_v3	r;

	r = multi_vec_by_n(n, 2 * dot(l, n));
	r = minus_vectors(r, l);
	return (r);
}
