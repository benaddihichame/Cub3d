/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncourtoi <ncourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:26:28 by ncourtoi          #+#    #+#             */
/*   Updated: 2025/01/13 16:06:07 by ncourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# define M_PI 3.14159265358979323846 /* pi */
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define BUFFER_SIZE 4096

// SCREEN
# define WIDTH 1300
# define HEIGHT 900
# define TILE_SIZE 22
# define FOV 60
# define NUM_RAYS 1280
# define MOVE_SPEED 5.0
# define ROT_SPEED 0.10

typedef struct s_texture
{
	mlx_texture_t	*texture;
	uint32_t		*pixels;
	uint32_t		width;
	uint32_t		height;
}					t_texture;

typedef struct s_player
{
	int				x;
	int				y;
	float			plyr_angl;
	double			ray_angle;
	double			distance;
	float			fov_rd;
	int				flag;
}					t_player;

typedef struct s_info
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		*ply;
	t_texture		*texture;
	float			tex_pos;
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	void			*win;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			start;
	int				i;
	int				f;
	int				c;
	char			**map;
	int				count;
	int				error_code;
	int				nblines;
	int				sizeline;
	int				emptyline;
	int				wrongchar;
	int				insidemap;
	int				path_len;
	int				res;
	int				rx;
	int				ry;
	int				dx;
	int				dy;
	int				px;
	int				py;
	int				multi;
	float			plyr_angl;
	double			ray_angle;
	double			distance;
	float			fov_rd;
	int				flag;
	double			v_x;
	double			v_y;
	double			h_x;
	double			h_y;
	bool			has_no;
	bool			has_so;
	bool			has_we;
	bool			has_ea;
	bool			has_f;
	bool			has_c;
	bool			colors_done;
	bool			texture_done;
	int				grid_x;
	int				grid_y;
	double			wall_h;
}					t_info;

// GNL
// GNL
char				*ft_sub_buff(char *buff, int y, int len);
int					ft_res_verif(const char *str);
int					ft_pathlen(char *str);
int					free_buff(char **buff);

// PARSING
int					ft_parsing(char *file, t_info *info);
int					basic_check(int ac, char **av);
int					parsing_color(char *str, t_info *info);
int					check_texture_type(char *str, t_info *info);
int					ft_mapping(char *str, t_info *info);
int					ft_parsing_next(char *file, t_info *info);
void				ft_init_arg(t_info *info);
int					ft_parsing(char *file, t_info *info);
int					basic_check(int ac, char **av);
int					parsing_color(char *str, t_info *info);
int					check_texture_type(char *str, t_info *info);
int					ft_mapping(char *str, t_info *info);
int					ft_parsing_next(char *file, t_info *info);
void				ft_init_arg(t_info *info);

// MAP
int					ft_verif_map(char *str, t_info *info);
int					ft_copymap(char *str, t_info *info);
int					ft_parsing_map(char *file, t_info *info);
int					adding_line(t_info *info, int fd);
int					check_closed(t_info *info, int x, int y, char target);

// VERIFICATION
int					check_line(char *str);
int					check_empty(char *str);

// UTILS
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *sub, unsigned int y, size_t len);
char				**ft_split(char *str, char c);
int					ft_isnum(char *str);
int					ft_atoi(const char *nptr);
int					ft_strlen(char *str);
int					ft_strchr(char *str, char c);
int					ft_strncmp(const char *s1, const char *s2,
						unsigned int len);
int					ft_isalpha(char c);
int					ft_isdigit(char c);
int					ft_strchr(char *str, char c);
int					ft_strcmp(char *s1, char *s2);
void				init_arg(t_info *info);
void				check_map_errors(t_info *info);
int					map_closed(t_info *info);

// MLX
void				draw_rays(t_info *info);
int					wall_hit_m(t_info *info, double x, double y);
void				close_windows(t_info *info);
void				draw_map(t_info *info);
void				key_hook(mlx_key_data_t keydata, void *param);
void				key_hook(mlx_key_data_t keydata, void *param);

// RAYTRACING
void				draw_3d_view(t_info *info);
void				cast_rays(t_info *info);
float				nor_angle(float angle);
int					init_wall_textures(t_info *info);

// CLEAR
void				close_callback(void *param);
void				free_map(char **map);
void				clean_path(t_info *info);
void				close_windows(t_info *info);
void				free_textures(t_info *info);
int					clean_remaining_lines(int fd);

// GNL
char				*ft_strchr_gnl_gnl(char *s, int c);
void				*ft_memset_gnl(void *s, int c, size_t n);
size_t				ft_strlen_gnl(const char *str);
char				*ft_strchr_gnl(char *s, int c);
char				*ft_strjoin_gnl(char *result, char *buffer);
char				*ft_update_buffer(char *buffer);
char				*ft_extract_line(char *buffer);
char				*ft_read_data(int fd, char *result);
char				*get_next_line(int fd);
int					init_wall_textures(t_info *info);
int					unit_circle(float angle, char c);
void				my_mlx_pixel_put(t_info *info, int x, int y, int color);
void				render_wall(t_info *info, int ray);

// CLEAR
void				close_callback(void *param);
void				free_map(char **map);
void				clean_path(t_info *info);
void				close_windows(t_info *info);
void				free_textures(t_info *info);
void				free_map(char **map);
void				clean_gnl(void);
void				free_game(t_info *info);

// KEYS
int					is_safe_position(t_info *info, float x, float y);
void				handle_escp(mlx_key_data_t keydata, t_info *info);

// RAYCASTING UTILS
void				my_mlx_pixel_put(t_info *info, int x, int y, int color);
int					reverse_bytes(int c);
float				nor_angle(float angle);
int					unit_circle(float angle, char c);

// RENDERING
void				draw_floor_ceilling(t_info *info, int ray, int t_pix,
						int b_pix);
mlx_texture_t		*get_texture(t_info *info, int flag);
double				get_x_o(t_info *info, mlx_texture_t *texture, int flag);
void				render_wall(t_info *info, int ray);

#endif
