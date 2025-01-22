/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:33:16 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 16:44:34 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_line_cleanup(char *line, int fd, t_info *info)
{
	free(line);
	close(fd);
	clean_remaining_lines(fd);
	clean_path(info);
	return (1);
}

int	process_texture(char *line, int fd, t_info *info)
{
	if (check_texture_type(line, info))
		return (handle_line_cleanup(line, fd, info));
	return (0);
}

int	process_color(char *line, int fd, t_info *info)
{
	if (info->colors_done)
		return (0);
	if (parsing_color(line, info))
		return (handle_line_cleanup(line, fd, info));
	return (0);
}

int	ft_parsing(char *file, t_info *info)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (info->colors_done && info->texture_done)
			ft_mapping(line, info);
		if (process_texture(line, fd, info))
			return (1);
		if (process_color(line, fd, info))
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (ft_parsing_next(file, info))
	{
		clean_path(info);
		return (1);
	}
	return (0);
}

int	ft_parsing_next(char *file, t_info *info)
{
	if (info->wrongchar == 2)
	{
		printf("Error: Wrong char detected\n");
		return (1);
	}
	if (info->sizeline == 0 || info->nblines == 0)
	{
		printf("Error: Map is missing or empty\n");
		return (1);
	}
	if (!info->no || !info->so || !info->we || !info->ea)
	{
		printf("Error: Missing texture path(s)\n");
		return (1);
	}
	if (info->f == -1 || info->c == -1)
	{
		printf("Error: Missing or invalid color definition\n");
		return (1);
	}
	ft_parsing_map(file, info);
	return (0);
}
