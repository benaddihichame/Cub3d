/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:25:31 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 15:27:04 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_player(t_info *info, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT)
	{
		info->plyr_angl -= ROT_SPEED;
		info->plyr_angl = nor_angle(info->plyr_angl);
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		info->plyr_angl += ROT_SPEED;
		info->plyr_angl = nor_angle(info->plyr_angl);
	}
}

void	calculate_movement(t_info *info, mlx_key_data_t keydata, float *move_x,
		float *move_y)
{
	if (keydata.key == MLX_KEY_W)
	{
		*move_x = roundf(cos(info->plyr_angl) * MOVE_SPEED);
		*move_y = roundf(sin(info->plyr_angl) * MOVE_SPEED);
	}
	else if (keydata.key == MLX_KEY_S)
	{
		*move_x = roundf(-cos(info->plyr_angl) * MOVE_SPEED);
		*move_y = roundf(-sin(info->plyr_angl) * MOVE_SPEED);
	}
	else if (keydata.key == MLX_KEY_A)
	{
		*move_x = cos(info->plyr_angl - M_PI / 2) * MOVE_SPEED;
		*move_y = sin(info->plyr_angl - M_PI / 2) * MOVE_SPEED;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		*move_x = cos(info->plyr_angl + M_PI / 2) * MOVE_SPEED;
		*move_y = sin(info->plyr_angl + M_PI / 2) * MOVE_SPEED;
	}
}

void	handle_key(t_info *info, mlx_key_data_t keydata, float *new_x,
		float *new_y)
{
	float	move_x;
	float	move_y;
	float	potential_x;
	float	potential_y;

	move_x = 0;
	move_y = 0;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		rotate_player(info, keydata);
		calculate_movement(info, keydata, &move_x, &move_y);
		potential_x = *new_x + move_x;
		potential_y = *new_y + move_y;
		if (is_safe_position(info, potential_x, *new_y))
			*new_x = potential_x;
		if (is_safe_position(info, *new_x, potential_y))
			*new_y = potential_y;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_info	*info;
	float	new_x;
	float	new_y;

	info = param;
	if (!info || !info->image || !info->mlx)
		return ;
	new_x = info->px;
	new_y = info->py;
	handle_escp(keydata, info);
	handle_key(info, keydata, &new_x, &new_y);
	if (new_x == info->px && new_y == info->py)
		return ;
	mlx_put_pixel(info->image, info->px, info->py, 0x00000000);
	if (new_x != info->px || new_y != info->py || keydata.key == MLX_KEY_LEFT
		|| keydata.key == MLX_KEY_RIGHT)
	{
		info->px = new_x;
		info->py = new_y;
	}
	mlx_put_pixel(info->image, info->px, info->py, 0xFF0000FF);
}
