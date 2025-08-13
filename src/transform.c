/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(float *y, float *z, float angle)
{
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(angle) + prev_z * sin(angle);
	*z = -prev_y * sin(angle) + prev_z * cos(angle);
}

void	rotate_y(float *x, float *z, float angle)
{
	float	prev_x;
	float	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(angle) - prev_z * sin(angle);
	*z = prev_x * sin(angle) + prev_z * cos(angle);
}

void	rotate_z(float *x, float *y, float angle)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle) + prev_y * sin(angle);
	*y = -prev_x * sin(angle) + prev_y * cos(angle);
}

void	apply_rotation(t_point *p, t_cam *cam)
{
	if (cam->x_angle != 0.0)
		rotate_x(&p->y, &p->z, cam->x_angle);
	if (cam->y_angle != 0.0)
		rotate_y(&p->x, &p->z, cam->y_angle);
	if (cam->z_angle != 0.0)
		rotate_z(&p->x, &p->y, cam->z_angle);
	if (isnan(p->x) || isinf(p->x))
		p->x = 0.0;
	if (isnan(p->y) || isinf(p->y))
		p->y = 0.0;
	if (isnan(p->z) || isinf(p->z))
		p->z = 0.0;
}
