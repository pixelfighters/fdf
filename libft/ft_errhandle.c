/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errhandle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:54:34 by kami              #+#    #+#             */
/*   Updated: 2025/08/13 12:32:51 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_errhandle(char *error_msg)
{
	write(STDERR_FILENO, KRED, 6);
	write(STDERR_FILENO, "Error", 5);
	write(STDERR_FILENO, KNRM, 5);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
