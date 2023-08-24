/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:27:58 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/24 17:58:23 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	openfile(char *filename)
{
	int	fd;

	if (ft_strlen2(filename) <= 3 || !validfilename(filename))
		parse_error("invalid filename\n", 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error("error : couldn't open file\n", 1);
	return (fd);
}

void	init_scene(t_scene *scene)
{
	scene->camera = NULL;
	scene->lights = NULL;
	scene->objects = NULL;
	scene->ambient_color = (t_v3){-1, -1, -1};
}

void	parseline(t_scene *scene, char **arr, int *i)
{
	if (!ft_strncmp("A", arr[0], 1))
	{
		(*i)++;
		ambient(scene, arr);
	}
	else if (!ft_strncmp("C", arr[0], 1))
	{
		(*i)++;
		camera(scene, arr);
	}
	else if (!ft_strncmp("L", arr[0], 1))
		light(scene, arr);
	else if (!ft_strncmp("sp", arr[0], 2))
		sp(scene, arr);
	else if (!ft_strncmp("pl", arr[0], 2))
		pl(scene, arr);
	else if (!ft_strncmp("cy", arr[0], 2))
		cy(scene, arr);
	else if (!ft_strncmp("cn", arr[0], 2))
		cn(scene, arr);
	else
		parse_error("invalid identifier\n", 3);
}

void	close_fd(int fd, int *i)
{
	close (fd);
	if (*i != 2)
		parse_error("1 Camera ,1 Light and 1 Ambient required\n", 20);
}

t_scene	*parse(char *filename)
{
	int		fd;
	int		i;
	char	*line;
	t_scene	*scene;

	i = 0;
	fd = openfile(filename);
	scene = malloc(sizeof(t_scene));
	init_scene(scene);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n' || *line == '#' || *line == '\0')
		{
			free(line);
			continue ;
		}
		spacer(line);
		parseline(scene, ft_split(line, ' '), &i);
		free(line);
	}
	close_fd (fd, &i);
	return (scene);
}
