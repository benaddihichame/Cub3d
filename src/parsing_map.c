/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:55:17 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 17:23:24 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_verif_map(char *str, t_info *info)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_strchr(str, '1') == 1 || ft_strchr(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' && str[i] != 'N'
				&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W'
				&& str[i] != '\n' && str[i] != '\t')
			{
				if (info->insidemap == 1)
					info->wrongchar = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	adding_line(t_info *info, int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (!str)
		return (0);
	info->insidemap = ft_verif_map(str, info);
	if (info->insidemap == 1)
	{
		info->count++;
		ft_copymap(str, info);
	}
	free(str);
	return (1);
}

int	init_map(t_info *info, int fd)
{
	info->map = malloc(sizeof(char *) * (info->nblines + 1));
	if (!info->map)
	{
		close(fd);
		return (1);
	}
	info->map[info->nblines] = NULL;
	return (0);
}

int	process_lines(t_info *info, int fd)
{
	int	ret;

	ret = adding_line(info, fd);
	while (ret > 0)
	{
		if (ret == -1)
		{
			free_map(info->map);
			close(fd);
			return (1);
		}
		ret = adding_line(info, fd);
	}
	return (0);
}

int	ft_parsing_map(char *file, t_info *info)
{
	int	fd;

	info->count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error: in the seconde read"), 1);
	if (init_map(info, fd))
		return (1);
	if (process_lines(info, fd))
		return (1);
	close(fd);
	check_map_errors(info);
	return (0);
}
