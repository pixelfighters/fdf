/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

const char	*get_view_name(t_view view)
{
	if (view == VIEW_ISO)
		return ("Isometric");
	if (view == VIEW_NORMAL)
		return ("Normal");
	if (view == VIEW_TOP)
		return ("Top");
	if (view == VIEW_SIDE)
		return ("Side");
	return ("Unknown");
}

const char	*get_color_mode_name(t_color_mode mode)
{
	if (mode == COLOR_HEIGHT)
		return ("Height");
	if (mode == COLOR_GRADIENT)
		return ("Gradient");
	if (mode == COLOR_ORIGINAL)
		return ("Original");
	if (mode == COLOR_SOLID)
		return ("Solid");
	return ("Unknown");
}

int	calculate_total_lines(t_fdf *fdf)
{
	int	horizontal_lines;
	int	vertical_lines;

	horizontal_lines = fdf->map->height * (fdf->map->width - 1);
	vertical_lines = fdf->map->width * (fdf->map->height - 1);
	return (horizontal_lines + vertical_lines);
}
