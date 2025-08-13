/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	handle_info_button_click(t_fdf *fdf, mouse_key_t button)
{
	if (button == MLX_MOUSE_BUTTON_LEFT && !fdf->show_info)
	{
		if (fdf->mouse->x >= 10 && fdf->mouse->x <= 50
			&& fdf->mouse->y >= fdf->mlx->height - 50
			&& fdf->mouse->y <= fdf->mlx->height - 10)
		{
			fdf->show_info = !fdf->show_info;
			draw_ui(fdf);
			return (1);
		}
	}
	return (0);
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_fdf	*fdf;

	(void)mods;
	fdf = (t_fdf *)param;
	if (!fdf || !fdf->mouse)
		return ;
	if (action == MLX_PRESS)
	{
		if (handle_info_button_click(fdf, button))
			return ;
		fdf->mouse->pressed = 1;
		fdf->mouse->button = button;
		fdf->mouse->prev_x = fdf->mouse->x;
		fdf->mouse->prev_y = fdf->mouse->y;
	}
	else if (action == MLX_RELEASE)
	{
		fdf->mouse->pressed = 0;
		fdf->mouse->button = 0;
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	(void)xdelta;
	fdf = (t_fdf *)param;
	if (!fdf || !fdf->mouse)
		return ;
	if (ydelta > 0)
		fdf->cam->zoom *= 1.1;
	else if (ydelta < 0)
		fdf->cam->zoom /= 1.1;
	if (fdf->cam->zoom < 0.1)
		fdf->cam->zoom = 0.1;
	if (fdf->cam->zoom > 100.0)
		fdf->cam->zoom = 100.0;
	draw_map(fdf);
	draw_ui(fdf);
}

static void	handle_mouse_drag(t_fdf *fdf, double dx, double dy)
{
	if (fdf->mouse->button == MLX_MOUSE_BUTTON_LEFT)
	{
		fdf->cam->x_offset += dx;
		fdf->cam->y_offset += dy;
	}
	else if (fdf->mouse->button == MLX_MOUSE_BUTTON_RIGHT)
	{
		fdf->cam->x_angle += dy * 0.01;
		fdf->cam->y_angle += dx * 0.01;
		validate_camera(fdf);
	}
	draw_map(fdf);
	draw_ui(fdf);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_fdf	*fdf;
	double	dx;
	double	dy;

	fdf = (t_fdf *)param;
	if (!fdf || !fdf->mouse)
		return ;
	dx = xpos - fdf->mouse->prev_x;
	dy = ypos - fdf->mouse->prev_y;
	if (fdf->mouse->pressed)
	{
		handle_mouse_drag(fdf, dx, dy);
		fdf->mouse->prev_x = xpos;
		fdf->mouse->prev_y = ypos;
	}
	fdf->mouse->x = xpos;
	fdf->mouse->y = ypos;
}
