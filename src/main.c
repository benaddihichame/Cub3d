/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:06:34 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 15:25:47 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_loop(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	mlx_delete_image(info->mlx, info->image);
	info->image = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	cast_rays(info);
	mlx_image_to_window(info->mlx, info->image, 0, 0);
}

void	start_game(t_info *info)
{
	info->px = info->dx * TILE_SIZE + TILE_SIZE / 2;
	info->py = info->dy * TILE_SIZE + TILE_SIZE / 2;
	info->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	info->ply = calloc(1, sizeof(t_player));
	mlx_loop_hook(info->mlx, game_loop, info);
	mlx_key_hook(info->mlx, key_hook, info);
	mlx_loop(info->mlx);
}

int	check_elements(char *line, t_info *info)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		info->has_no = true;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		info->has_so = true;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		info->has_we = true;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		info->has_ea = true;
	else if (ft_strncmp(line, "F ", 2) == 0)
		info->has_f = true;
	else if (ft_strncmp(line, "C ", 2) == 0)
		info->has_c = true;
	return (0);
}

int	check_required_elements(char *file, t_info *info)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = line;
		while (*tmp && *tmp == ' ')
			tmp++;
		check_elements(tmp, info);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (!(info->has_no && info->has_so && info->has_we && info->has_ea
			&& info->has_f && info->has_c));
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (basic_check(ac, av) != 1)
		return (1);
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	init_arg(info);
	if (check_required_elements(av[1], info))
	{
		printf("Error\nMissing required elements in map\n");
		return (free(info), 1);
	}
	if (ft_parsing(av[1], info) == 1)
		return (free(info), 1);
	if (init_wall_textures(info))
		return (free(info), 1);
	start_game(info);
	close_windows(info);
	mlx_terminate(info->mlx);
	free(info);
	return (0);
}
