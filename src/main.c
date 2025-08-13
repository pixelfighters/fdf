/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:49:23 by fschuh            #+#    #+#             */
/*   Updated: 2025/08/13 15:49:25 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		error_exit("Usage: ./fdf <map.fdf>");
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".fdf", 4) != 0)
		error_exit("Invalid file format. Use .fdf files");
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	check_args(argc, argv);
	fdf = init_fdf(argv[1]);
	if (!fdf)
		error_exit("Failed to load map - file may be too large or corrupted");
	draw_title(fdf);
	draw_map(fdf);
	draw_ui(fdf);
	mlx_key_hook(fdf->mlx, key_hook, fdf);
	mlx_mouse_hook(fdf->mlx, mouse_hook, fdf);
	mlx_scroll_hook(fdf->mlx, scroll_hook, fdf);
	mlx_cursor_hook(fdf->mlx, cursor_hook, fdf);
	mlx_loop(fdf->mlx);
	cleanup_fdf(fdf);
	return (0);
}
