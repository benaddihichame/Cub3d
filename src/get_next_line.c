/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:03:26 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 15:29:39 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_update_buffer(char *buffer)
{
	char	*new_buffer;
	int		len;
	int		j;

	len = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	if (!buffer[len])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen_gnl(buffer) - len + 1));
	if (!new_buffer)
		return (NULL);
	len++;
	j = 0;
	while (buffer[len])
		new_buffer[j++] = buffer[len++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		len;

	len = 0;
	if (!buffer[len])
		return (NULL);
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
	{
		line[len] = buffer[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_read_data(int fd, char *result)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	ft_memset_gnl(buffer, 0, BUFFER_SIZE);
	while (!ft_strchr_gnl(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		buffer[bytes] = '\0';
		result = ft_strjoin_gnl(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_read_data(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	result = ft_extract_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (result);
}
