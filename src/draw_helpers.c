/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:48:53 by fschuh            #+#    #+#             */
/*   Updated: 2025/08/13 15:48:56 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_pixel_color(t_draw_params *params, int current_x, int current_y)
{
	float	ratio;

	if (params->data->dx > params->data->dy && params->data->dx > 0)
		ratio = (float)abs(current_x - params->data->x0)
			/ (float)params->data->dx;
	else if (params->data->dy > 0)
		ratio = (float)abs(current_y - params->data->y0)
			/ (float)params->data->dy;
	else
		ratio = 0;
	return (interpolate_color(get_point_color(params->p1, params->fdf),
			get_point_color(params->p2, params->fdf), ratio));
}

static void	update_line_coords(t_draw_params *params, int *current_x,
	int *current_y)
{
	int	e2;

	e2 = 2 * params->data->err;
	if (e2 > -params->data->dy)
	{
		params->data->err -= params->data->dy;
		*current_x += params->data->sx;
	}
	if (e2 < params->data->dx)
	{
		params->data->err += params->data->dx;
		*current_y += params->data->sy;
	}
}

void	draw_line_pixels(mlx_image_t *img, t_draw_params *params)
{
	int	current_x;
	int	current_y;
	int	color;

	current_x = params->data->x0;
	current_y = params->data->y0;
	while (1)
	{
		if (current_x >= 0 && current_x < (int)img->width
			&& current_y >= 0 && current_y < (int)img->height)
		{
			color = get_pixel_color(params, current_x, current_y);
			put_pixel(img, current_x, current_y, color);
		}
		if (current_x == params->data->x1 && current_y == params->data->y1)
			break ;
		update_line_coords(params, &current_x, &current_y);
	}
}
