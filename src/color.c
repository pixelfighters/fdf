/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height_color(float z, float z_min, float z_max)
{
	float	ratio;
	int		r;
	int		g;
	int		b;

	if (z_max == z_min)
		return (COLOR_WHITE);
	ratio = (z - z_min) / (z_max - z_min);
	if (ratio < 0.5)
	{
		r = (int)(255 * ratio * 2);
		g = 255;
		b = 255 - (int)(255 * ratio * 2);
	}
	else
	{
		r = 255;
		g = 255 - (int)(255 * (ratio - 0.5) * 2);
		b = 0;
	}
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

int	interpolate_color(int c1, int c2, float ratio)
{
	int	r;
	int	g;
	int	b;

	if (ratio < 0.0)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	r = ((c1 >> 24) & 0xFF);
	r += (int)(ratio * (((c2 >> 24) & 0xFF) - ((c1 >> 24) & 0xFF)));
	g = ((c1 >> 16) & 0xFF);
	g += (int)(ratio * (((c2 >> 16) & 0xFF) - ((c1 >> 16) & 0xFF)));
	b = ((c1 >> 8) & 0xFF);
	b += (int)(ratio * (((c2 >> 8) & 0xFF) - ((c1 >> 8) & 0xFF)));
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

int	get_brightness(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	return ((r * 299 + g * 587 + b * 114) / 1000);
}

int	generate_random_color(void)
{
	return (((rand() % 256) << 24) | ((rand() % 256) << 16)
		| ((rand() % 256) << 8) | 0xFF);
}

int	get_point_color(t_point *p, t_fdf *fdf)
{
	float	ratio;
	int		color1;
	int		color2;

	if (fdf->color_mode == COLOR_ORIGINAL && p->has_color)
		return (p->color);
	else if (fdf->color_mode == COLOR_HEIGHT)
		return (get_height_color(p->z, fdf->map->z_min, fdf->map->z_max));
	else if (fdf->color_mode == COLOR_GRADIENT)
	{
		if (get_brightness(fdf->bg_color) > 128)
			color1 = 0x00000044;
		else
			color1 = 0xFFFFFFBB;
		color2 = fdf->gradient_color;
		ratio = ((float)p->orig_x + (float)p->orig_y)
			/ ((float)(fdf->map->width - 1) + (float)(fdf->map->height - 1));
		return (interpolate_color(color1, color2, ratio));
	}
	else if (fdf->color_mode == COLOR_SOLID)
		return (fdf->line_color);
	return (COLOR_WHITE);
}
