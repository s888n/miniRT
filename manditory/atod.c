/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:01:45 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/25 20:38:30 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	valid_double(double dbl)
{
	if (dbl >= __DBL_MAX__ || dbl <= __FLT_MIN__)
		parse_error("Error: double overflow", 69);
}

static void	init_vars(double *a, double *b, double *c, double *d)
{
	*a = 0;
	*b = 1;
	*c = 1;
	*d = 0;
}

double	ft_atod(char *n)
{
	t_abc	abc;

	init_vars(&abc.a, &abc.b, &abc.c, &abc.delta);
	if (*n == '-')
	{
		abc.c *= -1;
		n++;
	}
	while (*n && ((*n >= '0' && *n <= '9') || *n == '.'))
	{
		if (abc.delta)
		{
			abc.b = abc.b / 10;
			abc.a = abc.a + (*n - '0') * abc.b;
		}
		else if (*n == '.')
			abc.delta++;
		else
			abc.a = abc.a * 10 + (*n - '0');
		n++;
	}
	valid_double(abc.a * abc.c);
	return (abc.a * abc.c);
}
