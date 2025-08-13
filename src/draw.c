/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	pixel = img->pixels + (y * img->width + x) * 4;
	pixel[0] = (color >> 24) & 0xFF;
	pixel[1] = (color >> 16) & 0xFF;
	pixel[2] = (color >> 8) & 0xFF;
	pixel[3] = color & 0xFF;
}

void	clear_image(mlx_image_t *img, int color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_line(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;
	t_point	orig1;
	t_point	orig2;

	orig1 = fdf->map->points[y][x];
	project_point(&orig1, &p1, fdf);
	orig2 = fdf->map->points[y + 1][x];
	project_point(&orig2, &p2, fdf);
	if (fabs(p1.x) < 50000 && fabs(p1.y) < 50000
		&& fabs(p2.x) < 50000 && fabs(p2.y) < 50000)
	{
		p1.z = orig1.z;
		p2.z = orig2.z;
		p1.orig_x = x;
		p1.orig_y = y;
		p2.orig_x = x;
		p2.orig_y = y + 1;
		draw_line(fdf->img, p1, p2, fdf);
	}
}

static void	draw_lines(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	orig1;

	orig1 = fdf->map->points[y][x];
	project_point(&orig1, &p1, fdf);
	if (x < fdf->map->width - 1)
		draw_horizontal_line(fdf, x, y);
	if (y < fdf->map->height - 1)
		draw_vertical_line(fdf, x, y);
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf->img, fdf->bg_color);
	if (!fdf->map || !fdf->map->points)
		return ;
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			draw_lines(fdf, x, y);
			x++;
		}
		y++;
	}
}
