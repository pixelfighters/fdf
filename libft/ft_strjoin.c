/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kami <kami@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:22:27 by fschuh            #+#    #+#             */
/*   Updated: 2024/06/11 12:46:49 by kami             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*returnstring;
	char	*start;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	returnstring = (char *)malloc(sizeof(char) * len + 1);
	if (!returnstring)
		return (NULL);
	start = returnstring;
	while (*s1)
	{
		*returnstring++ = *s1++;
	}
	while (*s2)
	{
		*returnstring++ = *s2++;
	}
	*returnstring = '\0';
	return (start);
}
