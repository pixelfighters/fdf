/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_info_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setup_panel_data(t_fdf *fdf, int *panel_data, t_rect *panel)
{
	panel_data[2] = (int)(fdf->mlx->width * 0.6);
	panel_data[3] = 460;
	panel_data[0] = 30;
	panel_data[1] = fdf->mlx->height - panel_data[3] - 30;
	panel->x = panel_data[0];
	panel->y = panel_data[1];
	panel->width = panel_data[2];
	panel->height = panel_data[3];
}

void	draw_all_sections(t_fdf *fdf, int *panel_data, int *i, int *y_pos)
{
	draw_info_header(fdf, panel_data, i, y_pos);
	draw_current_state(fdf, panel_data[0], y_pos, i);
	draw_zoom_info(fdf, panel_data[0], y_pos, i);
	draw_map_stats(fdf, panel_data[0], y_pos, i);
	draw_controls(fdf, panel_data[0], y_pos, i);
}

void	init_info_texts(t_fdf *fdf, int *panel_data)
{
	(void)panel_data;
	fdf->info_text_count = 20;
	fdf->info_texts = malloc(sizeof(mlx_image_t *) * fdf->info_text_count);
}

void	draw_info_header(t_fdf *fdf, int *panel_data, int *i, int *y_pos)
{
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx,
			"FDF Info - Press I to toggle", panel_data[0] + 10, *y_pos);
	*y_pos += 30;
}
