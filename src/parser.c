/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*extract_point_string(char **start, char **end)
{
	char	*point_str;

	while (**start == ' ')
		(*start)++;
	if (!**start)
		return (NULL);
	*end = *start;
	while (**end && **end != ' ')
		(*end)++;
	point_str = malloc(*end - *start + 1);
	if (!point_str)
		return (NULL);
	ft_memcpy(point_str, *start, *end - *start);
	point_str[*end - *start] = '\0';
	if (point_str[*end - *start - 1] == '\n')
		point_str[*end - *start - 1] = '\0';
	return (point_str);
}

static int	parse_line(char *line, t_map *map, int y)
{
	char	*start;
	char	*end;
	char	*point_str;
	int		x;

	x = 0;
	start = line;
	while (*start && x < map->width)
	{
		point_str = extract_point_string(&start, &end);
		if (!point_str)
			break ;
		if (!parse_point(point_str, &map->points[y][x], x, y))
		{
			free(point_str);
			return (0);
		}
		free(point_str);
		x++;
		start = end;
	}
	return (x == map->width);
}

static int	process_map_line(int fd, t_map *map, int y)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	if (!parse_line(line, map, y))
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

static int	read_map(char *filename, t_map *map)
{
	int		fd;
	int		y;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	while (y < map->height)
	{
		result = process_map_line(fd, map, y);
		if (result <= 0)
		{
			close(fd);
			return (result == -1 && y == map->height);
		}
		y++;
	}
	close(fd);
	return (1);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->points = NULL;
	if (!get_map_dimensions(filename, map))
	{
		free(map);
		return (NULL);
	}
	if (!allocate_map(map))
	{
		free(map);
		return (NULL);
	}
	if (!read_map(filename, map))
	{
		free_map(map);
		return (NULL);
	}
	find_z_limits(map);
	return (map);
}
