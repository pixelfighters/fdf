/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_current_state(t_fdf *fdf, int x, int *y_pos, int *i)
{
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "Current State:",
			x + 10, *y_pos);
	*y_pos += 25;
	draw_view_info(fdf, x, y_pos, i);
	draw_color_info(fdf, x, y_pos, i);
}

void	draw_zoom_info(t_fdf *fdf, int x, int *y_pos, int *i)
{
	char	*temp_str;
	char	*display_str;

	temp_str = ft_strjoin("  Zoom: ", ft_itoa((int)fdf->cam->zoom));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  Zoom: N/A";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 20;
	temp_str = ft_strjoin("  Z-scale: ",
			ft_itoa((int)(fdf->cam->z_scale * 10)));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  Z-scale: N/A";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 30;
}

void	draw_map_stats(t_fdf *fdf, int x, int *y_pos, int *i)
{
	char	*temp_str;
	char	*display_str;

	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "Map Statistics:",
			x + 10, *y_pos);
	*y_pos += 25;
	temp_str = ft_strjoin("  Grid: ", ft_itoa(fdf->map->width));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  Grid: N/A";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 20;
	draw_points_lines_info(fdf, x, y_pos, i);
}

void	draw_controls(t_fdf *fdf, int x, int *y_pos, int *i)
{
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "Controls:",
			x + 10, *y_pos);
	*y_pos += 25;
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "  1-4: Change view",
			x + 10, *y_pos);
	*y_pos += 20;
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "  WASD: Move",
			x + 10, *y_pos);
	*y_pos += 20;
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "  Q/E: Z scale",
			x + 10, *y_pos);
	*y_pos += 20;
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "  Mouse: Rotate/Zoom",
			x + 10, *y_pos);
	*y_pos += 20;
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "  C: Color mode",
			x + 10, *y_pos);
	*y_pos += 20;
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, "  R: Reset",
			x + 10, *y_pos);
}
