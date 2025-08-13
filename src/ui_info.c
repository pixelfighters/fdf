/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_info_panel(t_fdf *fdf, t_rect *rect)
{
	if (rect->y < 100)
		rect->y = 100;
	draw_background_panel(fdf, rect);
}

void	draw_info_overlay(t_fdf *fdf)
{
	int		panel_data[4];
	int		i;
	int		y_pos;
	t_rect	panel;

	delete_info_texts(fdf);
	setup_panel_data(fdf, panel_data, &panel);
	draw_info_panel(fdf, &panel);
	init_info_texts(fdf, panel_data);
	if (!fdf->info_texts)
		return ;
	i = 0;
	y_pos = panel_data[1] + 10;
	draw_all_sections(fdf, panel_data, &i, &y_pos);
	fdf->info_text_count = i;
}
