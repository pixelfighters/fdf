/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_overlay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	delete_info_texts(t_fdf *fdf)
{
	int	i;

	if (fdf->info_texts)
	{
		i = 0;
		while (i < fdf->info_text_count)
		{
			if (fdf->info_texts[i])
				mlx_delete_image(fdf->mlx, fdf->info_texts[i]);
			i++;
		}
		free(fdf->info_texts);
		fdf->info_texts = NULL;
		fdf->info_text_count = 0;
	}
}

void	draw_background_panel(t_fdf *fdf, t_rect *rect)
{
	int	i;
	int	j;
	int	bg_color;

	bg_color = 0x000000aa;
	j = 0;
	while (j < rect->height)
	{
		i = 0;
		while (i < rect->width)
		{
			if (rect->x + i < (int)fdf->mlx->width
				&& rect->y + j < (int)fdf->mlx->height)
				put_pixel(fdf->ui_img, rect->x + i, rect->y + j, bg_color);
			i++;
		}
		j++;
	}
}

void	draw_ascii_art(t_fdf *fdf)
{
	(void)fdf;
}
