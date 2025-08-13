/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	line_out_of_bounds(t_point p1, t_point p2, mlx_image_t *img)
{
	int		margin;
	float	dx;
	float	dy;

	margin = 1000;
	dx = fabs(p1.x - p2.x);
	dy = fabs(p1.y - p2.y);
	if ((p1.x < -margin && p2.x < -margin)
		|| (p1.x > (int)img->width + margin && p2.x > (int)img->width + margin)
		|| (p1.y < -margin && p2.y < -margin)
		|| (p1.y > (int)img->height + margin
			&& p2.y > (int)img->height + margin))
		return (1);
	if (dx > img->width || dy > img->height)
		return (1);
	return (0);
}

void	draw_horizontal_line(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;
	t_point	orig1;
	t_point	orig2;

	orig1 = fdf->map->points[y][x];
	project_point(&orig1, &p1, fdf);
	orig2 = fdf->map->points[y][x + 1];
	project_point(&orig2, &p2, fdf);
	if (fabs(p1.x) < 50000 && fabs(p1.y) < 50000
		&& fabs(p2.x) < 50000 && fabs(p2.y) < 50000)
	{
		p1.z = orig1.z;
		p2.z = orig2.z;
		p1.orig_x = x;
		p1.orig_y = y;
		p2.orig_x = x + 1;
		p2.orig_y = y;
		draw_line(fdf->img, p1, p2, fdf);
	}
}

void	draw_line(mlx_image_t *img, t_point p1, t_point p2, t_fdf *fdf)
{
	t_line_data		data;
	t_draw_params	params;

	if (line_out_of_bounds(p1, p2, img))
		return ;
	data.x0 = (int)p1.x;
	data.y0 = (int)p1.y;
	data.x1 = (int)p2.x;
	data.y1 = (int)p2.y;
	data.dx = abs(data.x1 - data.x0);
	data.dy = abs(data.y1 - data.y0);
	if (data.x0 < data.x1)
		data.sx = 1;
	else
		data.sx = -1;
	if (data.y0 < data.y1)
		data.sy = 1;
	else
		data.sy = -1;
	data.err = data.dx - data.dy;
	params.p1 = &p1;
	params.p2 = &p2;
	params.data = &data;
	params.fdf = fdf;
	draw_line_pixels(img, &params);
}
