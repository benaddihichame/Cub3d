/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:14:10 by hbenaddi          #+#    #+#             */
/*   Updated: 2025/01/13 15:30:41 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_game(t_info *info)
{
	if (info && info->ply)
	{
		free(info->ply);
		info->ply = NULL;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	clean_path(t_info *info)
{
	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->ea)
		free(info->ea);
	if (info->we)
		free(info->we);
	info->no = NULL;
	info->so = NULL;
	info->ea = NULL;
	info->we = NULL;
}

void	free_textures(t_info *info)
{
	if (info->no_tex)
	{
		mlx_delete_texture(info->no_tex);
		info->no_tex = NULL;
	}
	if (info->so_tex)
	{
		mlx_delete_texture(info->so_tex);
		info->so_tex = NULL;
	}
	if (info->ea_tex)
	{
		mlx_delete_texture(info->ea_tex);
		info->ea_tex = NULL;
	}
	if (info->we_tex)
	{
		mlx_delete_texture(info->we_tex);
		info->we_tex = NULL;
	}
}

void	close_windows(t_info *info)
{
	if (!info)
		return ;
	if (info->mlx)
	{
		if (info->image)
			mlx_delete_image(info->mlx, info->image);
		mlx_close_window(info->mlx);
		free_textures(info);
		clean_path(info);
		free_map(info->map);
		free_game(info);
		mlx_terminate(info->mlx);
	}
	free(info);
	exit(0);
}
