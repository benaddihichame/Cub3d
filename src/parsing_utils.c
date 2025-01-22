/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:23:34 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 15:20:12 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	plyr_rotation(t_info *info)
{
	if (info->start == 'N')
		info->plyr_angl = M_PI;
	else if (info->start == 'S')
		info->plyr_angl = 0;
	else if (info->start == 'E')
		info->plyr_angl = M_PI / 2;
	else if (info->start == 'W')
		info->plyr_angl = (3 * M_PI) / 2;
}

int	ft_start(char c, t_info *info, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (info->start != 'x')
		{
			info->multi = 1;
			return (-1);
		}
		info->start = c;
		info->dx = j;
		info->dy = i;
		plyr_rotation(info);
		return (1);
	}
	return (0);
}

int	ft_emptyline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

int	ft_copymap(char *str, t_info *info)
{
	int	j;
	int	current_line;

	current_line = info->count - 1;
	j = 0;
	info->map[current_line] = malloc(sizeof(char) * (info->sizeline + 1));
	if (!info->map[current_line])
		return (-1);
	while (str[j] != '\0')
	{
		if (ft_start(str[j], info, current_line, j) == 1)
			info->map[current_line][j] = '0';
		else if (str[j] == ' ')
			info->map[current_line][j] = '0';
		else
			info->map[current_line][j] = str[j];
		j++;
	}
	while (j < info->sizeline)
	{
		info->map[current_line][j] = '0';
		j++;
	}
	info->map[current_line][j] = '\0';
	return (0);
}
