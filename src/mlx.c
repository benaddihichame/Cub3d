/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:43:10 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 14:18:14 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_info *info)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= info->nblines || x_m >= info->sizeline))
		return (0);
	if (info->map[y_m] && x_m <= (int)strlen(info->map[y_m]))
		if (info->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_info *info, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(info->py / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = info->px + (h_y - info->py) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, info))
	{
		h_x += x_step;
		h_y += y_step;
	}
	info->h_x = h_x;
	info->h_y = h_y;
	return (sqrt(pow(h_x - info->px, 2) + pow(h_y - info->py, 2)));
}

float	get_v_inter(t_info *info, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(info->px / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = info->py + (v_x - info->px) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x')
			&& y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, info))
	{
		v_x += x_step;
		v_y += y_step;
	}
	info->v_x = v_x;
	info->v_y = v_y;
	return (sqrt(pow(v_x - info->px, 2) + pow(v_y - info->py, 2)));
}

void	cast_rays(t_info *info)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	info->ray_angle = info->plyr_angl - (info->fov_rd / 2);
	while (ray < WIDTH)
	{
		info->flag = 0;
		h_inter = get_h_inter(info, nor_angle(info->ray_angle));
		v_inter = get_v_inter(info, nor_angle(info->ray_angle));
		if (v_inter <= h_inter)
			info->distance = v_inter;
		else
		{
			info->distance = h_inter;
			info->flag = 1;
		}
		render_wall(info, ray);
		ray++;
		info->ray_angle += (info->fov_rd / WIDTH);
	}
}
