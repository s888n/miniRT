/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:51:44 by srachdi           #+#    #+#             */
/*   Updated: 2022/11/23 10:50:39 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

int	ft_strchr2(char *str, int c)
{
	if (!str)
		return (0);
	while (*str && *str != (char)c)
		str++;
	if (*str == (char)c)
		return (1);
	return (0);
}

char	*ft_strjoin2(char *storage, char *readstr)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!storage)
	{
		storage = (char *)malloc(1 * sizeof(char));
		storage[0] = '\0';
	}
	if (!storage || !readstr)
		return (NULL);
	i = ft_strlen2(storage) + ft_strlen2(readstr);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (storage)
		while (storage[++i] != '\0')
			str[i] = storage[i];
	while (readstr[j] != '\0')
		str[i++] = readstr[j++];
	str[ft_strlen2(storage) + ft_strlen2(readstr)] = '\0';
	free(storage);
	return (str);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (s1[i] != s2[i])
			return (1);
	return (0);
}
