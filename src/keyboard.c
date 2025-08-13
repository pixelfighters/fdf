/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_view_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_1)
		fdf->cam->view = VIEW_ISO;
	else if (keydata.key == MLX_KEY_2)
		fdf->cam->view = VIEW_NORMAL;
	else if (keydata.key == MLX_KEY_3)
		fdf->cam->view = VIEW_TOP;
	else if (keydata.key == MLX_KEY_4)
		fdf->cam->view = VIEW_SIDE;
}

static void	handle_color_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_C)
	{
		fdf->color_mode = (fdf->color_mode + 1) % 4;
	}
	else if (keydata.key == MLX_KEY_SPACE)
	{
		fdf->bg_color = generate_random_color();
		fdf->gradient_color = generate_random_color();
		if (get_brightness(fdf->bg_color) > 128)
			fdf->line_color = COLOR_BLACK;
		else
			fdf->line_color = COLOR_WHITE;
	}
}

static void	handle_movement_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_W)
		fdf->cam->y_offset -= 20;
	else if (keydata.key == MLX_KEY_S)
		fdf->cam->y_offset += 20;
	else if (keydata.key == MLX_KEY_A)
		fdf->cam->x_offset -= 20;
	else if (keydata.key == MLX_KEY_D)
		fdf->cam->x_offset += 20;
	else if (keydata.key == MLX_KEY_Q)
		fdf->cam->z_scale += 0.1;
	else if (keydata.key == MLX_KEY_E)
		fdf->cam->z_scale -= 0.1;
	if (fdf->cam->z_scale < 0.1)
		fdf->cam->z_scale = 0.1;
}

static void	handle_ui_keys(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_I)
		fdf->show_info = !fdf->show_info;
	else if (keydata.key == MLX_KEY_SLASH)
		fdf->show_info = !fdf->show_info;
	else if (keydata.key == MLX_KEY_R)
		reset_camera(fdf);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (!fdf || !fdf->cam || !fdf->map)
		return ;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	else
	{
		handle_view_keys(keydata, fdf);
		handle_color_keys(keydata, fdf);
		handle_movement_keys(keydata, fdf);
		handle_ui_keys(keydata, fdf);
		draw_map(fdf);
		draw_ui(fdf);
	}
}
