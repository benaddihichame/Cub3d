/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:21:41 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/09 18:55:56 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_floor_ceilling(t_info *info, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	while (i < HEIGHT)
		my_mlx_pixel_put(info, ray, i++, info->f);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(info, ray, i++, info->c);
}

mlx_texture_t	*get_texture(t_info *info, int flag)
{
	info->ray_angle = nor_angle(info->ray_angle);
	if (flag == 0)
	{
		if (info->ray_angle > M_PI / 2 && info->ray_angle < 3 * (M_PI / 2))
			return (info->no_tex);
		else
			return (info->so_tex);
	}
	else
	{
		if (info->ray_angle > 0 && info->ray_angle < M_PI)
			return (info->ea_tex);
		else
			return (info->we_tex);
	}
}

double	get_x_o(t_info *info, mlx_texture_t *texture, int flag)
{
	double	x_o;

	if (flag == 1)
		x_o = (int)fmodf((info->h_x * (texture->width / TILE_SIZE)),
				texture->width);
	else
		x_o = (int)fmodf((info->v_y * (texture->width / TILE_SIZE)),
				texture->width);
	return (x_o);
}

void	draw_wall(t_info *info, int ray, int t_pix, int b_pix)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture_t;
	uint32_t		*arr;
	double			factor;

	texture_t = get_texture(info, info->flag);
	arr = (uint32_t *)texture_t->pixels;
	factor = (double)texture_t->height / info->wall_h;
	x_o = get_x_o(info, texture_t, info->flag);
	y_o = (t_pix - (HEIGHT / 2) + (info->wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(info, ray, t_pix, reverse_bytes(arr[(int)y_o
				* texture_t->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_info *info, int ray)
{
	double	b_pix;
	double	t_pix;

	info->distance *= cos(nor_angle(info->ray_angle - info->plyr_angl));
	info->wall_h = (TILE_SIZE / info->distance)
		* ((WIDTH / 2) / tan(info->fov_rd / 2));
	b_pix = (HEIGHT / 2) + (info->wall_h / 2);
	t_pix = (HEIGHT / 2) - (info->wall_h / 2);
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0)
	{
		t_pix = 0;
	}
	draw_wall(info, ray, t_pix, b_pix);
	draw_floor_ceilling(info, ray, t_pix, b_pix);
}
