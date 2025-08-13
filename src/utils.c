/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->points)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->points[i])
				free(map->points[i]);
			i++;
		}
		free(map->points);
	}
	free(map);
}
