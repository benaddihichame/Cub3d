/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:06:32 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 17:23:31 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_verif_mapping(char *str, t_info *info)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
			&& str[i] != '\t')
			return (info->wrongchar = 2, 0);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			if ((str[i - 1] != '0' && str[i - 1] != '1') || (str[i + 1] != '\0'
					&& str[i + 1] != '0' && str[i + 1] != '1'))
				return (info->wrongchar = 2, 0);
		}
		i++;
	}
	return (1);
}

int	ft_mapping(char *str, t_info *info)
{
	static int	v_nblines = 0;
	static int	v_sizeline = 0;
	int			i;

	i = 0;
	if (ft_verif_mapping(str, info) == 1)
	{
		i = ft_strlen(str);
		if (i > v_sizeline)
			v_sizeline = i;
		if (!check_empty(str))
			v_nblines -= 1;
		v_nblines += 1;
	}
	info->nblines = v_nblines;
	info->sizeline = v_sizeline;
	return (0);
}
