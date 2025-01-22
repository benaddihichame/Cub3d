/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:20:10 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 16:04:20 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_valid_path(char *str)
{
	int	fd;

	if (!ft_strchr(str, '.') || !ft_strchr(str, '/') || ft_pathlen(str) <= 2)
		return (false);
	while (*str != '.')
		str++;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: File %s does not exist\n", str);
		return (false);
	}
	close(fd);
	return (true);
}

bool	is_valid_extension(char *path)
{
	int	len;

	if (!path)
		return (false);
	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (ft_strncmp(path + len - 4, ".png", 4) == 0)
		return (true);
	return (false);
}

int	texture_path(char *str, char **texture, t_info *info, int j)
{
	char	*new_texture;

	info->path_len = 0;
	if (!is_valid_path(str))
		return (1);
	while (str[j] && (str[j] == ' ' || str[j] == '\t'))
		j++;
	if (str[j] != '.' || str[j + 1] != '/')
		return (1);
	new_texture = (char *)(malloc(sizeof(char) * (ft_pathlen(str) + 1)));
	if (!new_texture)
		return (1);
	while (str[j] != '\0' && info->path_len < ft_pathlen(str))
	{
		new_texture[info->path_len] = str[j];
		info->path_len++;
		j++;
	}
	new_texture[info->path_len] = '\0';
	if (!is_valid_path(new_texture))
		return (free(new_texture), 1);
	if (*texture)
		free(*texture);
	*texture = new_texture;
	return (0);
}

int	check_valid_texture(char *str, t_info *info, int *ret)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && !info->no)
	{
		if (is_valid_extension(str) == true)
			*ret = texture_path(str, &info->no, info, str - str + 3);
		return (1);
	}
	if (ft_strncmp(str, "SO ", 3) == 0 && !info->so)
	{
		if (is_valid_extension(str) == true)
			*ret = texture_path(str, &info->so, info, str - str + 3);
		return (1);
	}
	if (ft_strncmp(str, "EA ", 3) == 0 && !info->ea)
	{
		if (is_valid_extension(str) == true)
			*ret = texture_path(str, &info->ea, info, str - str + 3);
		return (1);
	}
	if (ft_strncmp(str, "WE ", 3) == 0 && !info->we)
	{
		if (is_valid_extension(str) == true)
			*ret = texture_path(str, &info->we, info, str - str + 3);
		return (1);
	}
	return (0);
}

int	check_texture_type(char *str, t_info *info)
{
	int	ret;

	if (!str)
		return (1);
	ret = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (!check_valid_texture(str, info, &ret))
	{
		if (ft_isalpha(str[0]) && ft_isalpha(str[1]))
			ret = 1;
	}
	if (ret)
	{
		printf("Error: Textures parsing\n");
		clean_path(info);
		return (1);
	}
	info->texture_done = (info->no && info->so && info->ea && info->we);
	return (0);
}
