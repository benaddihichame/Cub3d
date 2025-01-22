/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:31:21 by hbenaddi          #+#    #+#             */
/*   Updated: 2025/01/13 15:24:01 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	basic_check(int ac, char **av)
{
	if (ac != 2)
	{
		printf("You must have 2 arguments\n");
		return (0);
	}
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		printf("The seconde argument is not .cub\n");
		return (0);
	}
	return (1);
}

int	check_closed(t_info *info, int x, int y, char target)
{
	char	current;

	if (y < 0 || y >= info->nblines || x < 0 || x >= info->sizeline)
		return (0);
	current = info->map[y][x];
	if (current == ' ' || current == '\n' || current == '\0')
		return (0);
	if (current == '1' || current == target)
		return (1);
	info->map[y][x] = target;
	if (check_closed(info, x + 1, y, target) == 0)
		return (0);
	if (check_closed(info, x - 1, y, target) == 0)
		return (0);
	if (check_closed(info, x, y + 1, target) == 0)
		return (0);
	if (check_closed(info, x, y - 1, target) == 0)
		return (0);
	return (1);
}
