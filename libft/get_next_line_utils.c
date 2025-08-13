/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kami <kami@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:20:24 by kami              #+#    #+#             */
/*   Updated: 2024/09/26 12:44:01 by kami             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_is_binary(char *buffer, ssize_t read_bytes)
{
	int	i;

	i = 0;
	while (i < read_bytes)
	{
		if (buffer[i] < 32 && buffer[i] != '\n'
			&& buffer[i] != '\t' && buffer[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_gnl_strjoin(char *buffer, char *content)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!buffer)
		return (ft_strdup(content));
	if (!content)
		return (ft_strdup(buffer));
	i = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(buffer)
				+ ft_strlen(content)) + 1);
	if (!result)
		return (NULL);
	while (buffer && buffer[i])
	{
		result[i] = buffer[i];
		i++;
	}
	j = 0;
	while (content && content[j])
		result[i++] = content[j++];
	result[i] = '\0';
	free(buffer);
	return (result);
}
