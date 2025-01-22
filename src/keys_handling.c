/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:37:01 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/09 17:01:00 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handle_escp(mlx_key_data_t keydata, t_info *info)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		close_windows(info);
}

int	safe_pos(t_info *info, float x_offset, float y_offset, float margin)
{
	if (x_offset < margin || x_offset > TILE_SIZE - margin || y_offset < margin
		|| y_offset > TILE_SIZE - margin)
	{
		if (info->map[info->grid_y][info->grid_x] == '1' || (x_offset < margin
				&& info->map[info->grid_y][info->grid_x - 1] == '1')
			|| (x_offset > TILE_SIZE - margin
				&& info->map[info->grid_y][info->grid_x + 1] == '1')
			|| (y_offset < margin && info->map[info->grid_y
				- 1][info->grid_x] == '1') || (y_offset > TILE_SIZE - margin
				&& info->map[info->grid_y + 1][info->grid_x] == '1'))
		{
			return (0);
		}
	}
	return (1);
}

int	is_safe_position(t_info *info, float x, float y)
{
	float	margin;
	float	x_offset;
	float	y_offset;

	info->grid_x = floor(x / TILE_SIZE);
	info->grid_y = floor(y / TILE_SIZE);
	margin = 5.0;
	if (info->grid_x < 0 || info->grid_y < 0 || info->grid_x >= info->sizeline
		|| info->grid_y >= info->nblines)
	{
		return (0);
	}
	if (info->map[info->grid_y][info->grid_x] == '1')
	{
		return (0);
	}
	x_offset = x - (info->grid_x * TILE_SIZE);
	y_offset = y - (info->grid_y * TILE_SIZE);
	if (safe_pos(info, x_offset, y_offset, margin) == 0)
		return (0);
	return (1);
}
