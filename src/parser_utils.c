/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	allocate_map(t_map *map)
{
	int	i;

	map->points = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->points[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	count_line_words(char *line)
{
	char	*ptr;
	int		width;

	ptr = line;
	width = 0;
	while (*ptr)
	{
		while (*ptr == ' ')
			ptr++;
		if (*ptr && ++width)
			while (*ptr && *ptr != ' ')
				ptr++;
	}
	return (width);
}

int	get_map_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map->width)
			map->width = count_line_words(line);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map->width > 0 && map->height > 0);
}
