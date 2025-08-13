/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_color_string(char *color_str)
{
	int	color;

	if (*color_str == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
		color_str += 2;
	color = 0;
	while (*color_str && color >= 0)
	{
		color <<= 4;
		if (*color_str >= '0' && *color_str <= '9')
			color |= *color_str - '0';
		else if (*color_str >= 'a' && *color_str <= 'f')
			color |= *color_str - 'a' + 10;
		else if (*color_str >= 'A' && *color_str <= 'F')
			color |= *color_str - 'A' + 10;
		else
			color = -1;
		color_str++;
	}
	if (color < 0)
		return (-1);
	return ((color << 8) | 0xFF);
}

int	parse_point(char *str, t_point *point, int x, int y)
{
	char	*comma;

	point->x = (float)x;
	point->y = (float)y;
	point->z = (float)ft_atoi(str);
	comma = ft_strchr(str, ',');
	if (!comma)
	{
		point->color = COLOR_WHITE;
		point->has_color = 0;
		return (1);
	}
	point->color = parse_color_string(comma + 1);
	if (point->color == -1)
	{
		point->color = COLOR_WHITE;
		point->has_color = 0;
	}
	point->has_color = 1;
	return (1);
}

void	find_z_limits(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->points)
		return ;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z < map->z_min)
				map->z_min = map->points[y][x].z;
			if (map->points[y][x].z > map->z_max)
				map->z_max = map->points[y][x].z;
			x++;
		}
		y++;
	}
	if (map->z_min == map->z_max)
		map->z_max = map->z_min + 1;
}
