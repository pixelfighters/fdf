/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cam	*init_camera(t_map *map)
{
	t_cam	*cam;
	float	scale_x;
	float	scale_y;

	cam = (t_cam *)malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	scale_x = WIN_WIDTH / (float)(map->width * 2);
	scale_y = WIN_HEIGHT / (float)(map->height * 2);
	cam->zoom = fmin(scale_x, scale_y);
	if (cam->zoom > 50.0)
		cam->zoom = 50.0;
	if (cam->zoom < 5.0)
		cam->zoom = 20.0;
	cam->x_offset = WIN_WIDTH / 2;
	cam->y_offset = WIN_HEIGHT / 2;
	cam->x_angle = 0.0;
	cam->y_angle = 0.0;
	cam->z_angle = 0.0;
	cam->z_scale = 1.0;
	cam->view = VIEW_ISO;
	return (cam);
}

void	reset_camera(t_fdf *fdf)
{
	float	scale_x;
	float	scale_y;

	scale_x = fdf->mlx->width / (float)(fdf->map->width * 2);
	scale_y = fdf->mlx->height / (float)(fdf->map->height * 2);
	fdf->cam->zoom = fmin(scale_x, scale_y);
	if (fdf->cam->zoom > 50.0)
		fdf->cam->zoom = 50.0;
	if (fdf->cam->zoom < 1.0)
		fdf->cam->zoom = 1.0;
	fdf->cam->x_offset = fdf->mlx->width / 2;
	fdf->cam->y_offset = fdf->mlx->height / 2;
	fdf->cam->x_angle = 0.0;
	fdf->cam->y_angle = 0.0;
	fdf->cam->z_angle = 0.0;
	fdf->cam->z_scale = 1.0;
	fdf->cam->view = VIEW_ISO;
}

void	validate_camera(t_fdf *fdf)
{
	if (fabs(fdf->cam->x_angle) > 2 * M_PI)
		fdf->cam->x_angle = fmod(fdf->cam->x_angle, 2 * M_PI);
	if (fabs(fdf->cam->y_angle) > 2 * M_PI)
		fdf->cam->y_angle = fmod(fdf->cam->y_angle, 2 * M_PI);
	if (fabs(fdf->cam->z_angle) > 2 * M_PI)
		fdf->cam->z_angle = fmod(fdf->cam->z_angle, 2 * M_PI);
}

t_mouse	*init_mouse(void)
{
	t_mouse	*mouse;

	mouse = (t_mouse *)malloc(sizeof(t_mouse));
	if (!mouse)
		return (NULL);
	mouse->pressed = 0;
	mouse->button = 0;
	mouse->x = 0;
	mouse->y = 0;
	mouse->prev_x = 0;
	mouse->prev_y = 0;
	return (mouse);
}

int	map_has_colors(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->points)
		return (0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].has_color)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
