/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:49 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 16:25:52 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	allowedchars(char c)
{
	if (c == ' ' || c == '\t' || \
		c == '\n' || ft_isdigit(c) \
		|| c == '.' || c == ',' || c == '-')
		return (1);
	return (0);
}

int	countchar(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s[++i])
		if (s[i] == c)
			count++;
	return (count);
}

int	validfilename(char *filename)
{
	if (!ft_strncmp(filename + (ft_strlen2(filename) - 3), ".rt", 3))
		return (1);
	return (0);
}

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
