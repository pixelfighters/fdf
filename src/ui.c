/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	toggle_info(t_fdf *fdf)
{
	fdf->show_info = !fdf->show_info;
}

void	draw_title(t_fdf *fdf)
{
	(void)fdf;
	ft_printf("Starting FDF - Wireframe 3D Viewer\n");
	ft_print_ascii_art("FDF", KGRN, 1);
}

void	draw_ui(t_fdf *fdf)
{
	clear_image(fdf->ui_img, 0x00000000);
	if (!fdf->title_text)
		fdf->title_text = mlx_put_string(fdf->mlx,
				"FDF - Wireframe 3D Viewer", 20, 20);
	if (fdf->show_info)
		draw_info_overlay(fdf);
	else
		delete_info_texts(fdf);
}
