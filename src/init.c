/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>

static int	init_mlx_images(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->ui_img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->question_img = mlx_new_image(fdf->mlx, 40, 40);
	if (!fdf->img || !fdf->ui_img || !fdf->question_img)
		return (0);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	mlx_image_to_window(fdf->mlx, fdf->ui_img, 0, 0);
	mlx_image_to_window(fdf->mlx, fdf->question_img, 10, WIN_HEIGHT - 50);
	fdf->img->instances[0].z = 0;
	fdf->ui_img->instances[0].z = 1;
	fdf->question_img->instances[0].z = 2;
	return (1);
}

static void	init_fdf_properties(t_fdf *fdf)
{
	if (map_has_colors(fdf->map))
		fdf->color_mode = COLOR_ORIGINAL;
	else
		fdf->color_mode = COLOR_SOLID;
	fdf->show_info = 1;
	fdf->bg_color = 0x222222FF;
	fdf->line_color = COLOR_WHITE;
	fdf->adaptive_color = 1;
	fdf->gradient_color = generate_random_color();
	fdf->title_text = NULL;
	fdf->info_texts = NULL;
	fdf->info_text_count = 0;
}

static t_fdf	*init_basic_fdf(char *filename)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = parse_map(filename);
	if (!fdf->map)
	{
		free(fdf);
		return (NULL);
	}
	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		free_map(fdf->map);
		free(fdf);
		return (NULL);
	}
	return (fdf);
}

t_fdf	*init_fdf(char *filename)
{
	t_fdf	*fdf;

	fdf = init_basic_fdf(filename);
	if (!fdf)
		return (NULL);
	if (!init_mlx_images(fdf))
	{
		cleanup_fdf(fdf);
		return (NULL);
	}
	fdf->cam = init_camera(fdf->map);
	fdf->mouse = init_mouse();
	if (!fdf->cam || !fdf->mouse)
	{
		cleanup_fdf(fdf);
		return (NULL);
	}
	init_fdf_properties(fdf);
	return (fdf);
}
