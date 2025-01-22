/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:00:48 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 16:41:38 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

bool	is_rgb_valid(char *str)
{
	int	i;
	int	count_comma;

	i = 0;
	count_comma = 0;
	while (str[i])
	{
		if (str[i] == '-')
			return (false);
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' ')
			return (false);
		if (str[i] == ',')
			count_comma++;
		i++;
	}
	if (count_comma != 2)
		return (false);
	return (true);
}

int	convert_rgb(char *str)
{
	int		rgb[3];
	int		i;
	char	**components;

	i = 0;
	if (is_rgb_valid(str) == false)
		return (0);
	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		free_split(components);
		return (0);
	}
	while (i < 3)
	{
		rgb[i] = ft_atoi(components[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_split(components), 0);
		i++;
	}
	free_split(components);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	parsing_color(char *str, t_info *info)
{
	static bool	f_done = false;
	static bool	c_done = false;

	if (!str)
		return (0);
	if (str[0] != 'F' && str[0] != 'C')
		return (0);
	if (str[0] == 'F')
	{
		info->f = convert_rgb(str + 2);
		if (info->f == 0)
			return (printf("Error with RGB\n"), 1);
		f_done = true;
	}
	else if (str[0] == 'C')
	{
		info->c = convert_rgb(str + 2);
		if (info->c == 0)
			return (printf("Error with RGB\n"), 1);
		c_done = true;
	}
	if (f_done && c_done)
		info->colors_done = true;
	return (0);
}
