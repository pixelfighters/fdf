/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sections_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_view_info(t_fdf *fdf, int x, int *y_pos, int *i)
{
	char	*temp_str;
	char	*display_str;

	temp_str = ft_strjoin("  View: ", get_view_name(fdf->cam->view));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  View: Unknown";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 20;
}

void	draw_color_info(t_fdf *fdf, int x, int *y_pos, int *i)
{
	char	*temp_str;
	char	*display_str;

	temp_str = ft_strjoin("  Color: ", get_color_mode_name(fdf->color_mode));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  Color: Unknown";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 20;
}

void	draw_points_lines_info(t_fdf *fdf, int x, int *y_pos, int *i)
{
	char	*temp_str;
	char	*display_str;

	temp_str = ft_strjoin("  Points: ",
			ft_itoa(fdf->map->width * fdf->map->height));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  Points: N/A";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 20;
	temp_str = ft_strjoin("  Lines: ", ft_itoa(calculate_total_lines(fdf)));
	if (temp_str)
		display_str = temp_str;
	else
		display_str = "  Lines: N/A";
	fdf->info_texts[(*i)++] = mlx_put_string(fdf->mlx, display_str,
			x + 10, *y_pos);
	if (temp_str)
		free(temp_str);
	*y_pos += 30;
}
