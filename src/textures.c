/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:03:35 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 15:19:31 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*load_wall_texture(char *path)
{
	mlx_texture_t	*tex;

	if (!path)
		return (NULL);
	tex = mlx_load_png(path);
	if (!tex)
	{
		printf("Failed \n");
		return (NULL);
	}
	return (tex);
}

int	init_wall_textures(t_info *info)
{
	if (!info->no || !info->so || !info->ea || !info->we)
		return (1);
	info->no_tex = load_wall_texture(info->no);
	info->so_tex = load_wall_texture(info->so);
	info->ea_tex = load_wall_texture(info->ea);
	info->we_tex = load_wall_texture(info->we);
	if (!info->no_tex || !info->so_tex || !info->ea_tex || !info->we_tex)
	{
		free_textures(info);
		return (1);
	}
	return (0);
}
