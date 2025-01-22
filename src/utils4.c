/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:11 by hbenaddi          #+#    #+#             */
/*   Updated: 2025/01/13 15:34:25 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	clean_remaining_lines(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (1);
}

void	check_map_errors(t_info *info)
{
	if (info->multi == 1)
	{
		printf("Error: Multiple players detected\n");
		clean_path(info);
		free_map(info->map);
		free(info);
		exit(1);
	}
	if (info->start == 'x')
	{
		printf("Error: No players detected\n");
		clean_path(info);
		free_map(info->map);
		free(info);
		exit(1);
	}
	if (map_closed(info) == 0)
	{
		printf("Error: Map not closed\n");
		clean_path(info);
		free_map(info->map);
		free(info);
		exit(1);
	}
}

int	map_closed(t_info *info)
{
	if (check_closed(info, info->dx, info->dy, 'V') == 0)
		return (0);
	check_closed(info, info->dx, info->dy, '0');
	return (1);
}
