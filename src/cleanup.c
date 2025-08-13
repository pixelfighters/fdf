/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:00 by fschuh          #+#    #+#             */
/*   Updated: 2025/01/10 14:00:00 by fschuh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	delete_info_texts(fdf);
	if (fdf->map)
		free_map(fdf->map);
	if (fdf->cam)
		free(fdf->cam);
	if (fdf->mouse)
		free(fdf->mouse);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	free(fdf);
}
