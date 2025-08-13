/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_point *p)
{
	float	prev_x;
	float	prev_y;

	prev_x = p->x;
	prev_y = p->y;
	p->x = (prev_x - prev_y) * 0.866;
	p->y = (prev_x + prev_y) * 0.5 - p->z;
}

void	apply_view(t_point *p, t_cam *cam)
{
	if (cam->view == VIEW_ISO)
		isometric_projection(p);
	else if (cam->view == VIEW_TOP)
	{
		p->x = p->x;
		p->y = p->y;
		p->z = 0;
	}
	else if (cam->view == VIEW_SIDE)
	{
		p->x = p->z;
		p->y = p->y;
	}
	else if (cam->view == VIEW_NORMAL)
	{
		p->x = p->x;
		p->y = p->y - p->z;
	}
}

static void	apply_transformations(t_point *dst, t_fdf *fdf)
{
	apply_rotation(dst, fdf->cam);
	apply_view(dst, fdf->cam);
	dst->x *= fdf->cam->zoom;
	dst->y *= fdf->cam->zoom;
	dst->x += fdf->cam->x_offset;
	dst->y += fdf->cam->y_offset;
	if (isnan(dst->x) || isinf(dst->x))
		dst->x = 0;
	if (isnan(dst->y) || isinf(dst->y))
		dst->y = 0;
}

void	project_point(t_point *src, t_point *dst, t_fdf *fdf)
{
	float	x_center;
	float	y_center;

	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z * fdf->cam->z_scale;
	dst->color = src->color;
	dst->has_color = src->has_color;
	x_center = fdf->map->width / 2.0;
	y_center = fdf->map->height / 2.0;
	dst->x -= x_center;
	dst->y -= y_center;
	apply_transformations(dst, fdf);
}
