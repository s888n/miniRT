/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:02:52 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 16:24:26 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	wordcount(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			while (*s && *s != c)
				s++;
			count++;
		}
	}
	return (count);
}

char	*ft_wd(char const *str, char c)
{
	size_t	i;
	char	*wd;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	wd = (char *)malloc(sizeof(char) * (i + 1));
	if (!wd)
		return (0);
	i = 0;
	while (*str && *str != c)
	{
		wd[i] = *str;
		i++;
		str++;
	}
	wd[i] = '\0';
	return (wd);
}

char	**fail_allo(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s1, char c)
{
	size_t	i;
	size_t	wc;
	char	**strings;

	i = 0;
	if (!s1)
		return (NULL);
	wc = wordcount(s1, c);
	strings = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!strings)
		return (0);
	while (i < wc)
	{
		while (*s1 && *s1 == c)
			s1++;
		strings[i] = ft_wd(s1, c);
		if (!strings[i])
			return (fail_allo(i, strings));
		while (*s1 && *s1 != c)
			s1++;
		i++;
	}
	strings[i] = 0;
	return (strings);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
