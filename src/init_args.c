/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:07:17 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 15:18:22 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_arg2(t_info *info)
{
	info->has_no = false;
	info->has_so = false;
	info->has_we = false;
	info->has_ea = false;
	info->has_f = false;
	info->has_c = false;
}

void	init_arg(t_info *info)
{
	info->ea = NULL;
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->colors_done = false;
	info->texture_done = false;
	info->colors_done = false;
	info->texture_done = false;
	info->error_code = 0;
	info->insidemap = 0;
	info->wrongchar = 0;
	info->map = NULL;
	info->c = -1;
	info->f = -1;
	info->count = 0;
	info->nblines = 0;
	info->multi = 0;
	info->sizeline = 0;
	info->start = 'x';
	info->image = NULL;
	info->plyr_angl = (3 * M_PI) / 2;
	info->fov_rd = (FOV * M_PI) / 180;
	init_arg2(info);
}
