/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:45:09 by georgii           #+#    #+#             */
/*   Updated: 2022/10/30 16:51:37 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64

# include <stdlib.h>
# include <stdio.h>
# include "../minilibx-opengl/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_parser {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		**map;
	int		min_len;
	int		floor[3];
	int		ceiling[3];
	int		map_height;
	int		map_width;
	double	x_orient;
	double	y_orient;
	int		pos_x;
	int		pos_y;
}	t_parser;

typedef struct s_geom
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			texture_height;
	int			texture_width;

	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	t_parser	*parser;

}	t_geom;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_img	img_data;
	t_geom	geom_data;
	t_img	tex[4];
	int		floor_color;
	int		ceiling_color;

}	t_data;

int		parser_init(t_parser *parser, int argc, char **argv, int fd);
int		parser_start(int fd, t_parser *parser);
int		parse_line(t_parser *parser, char *line);
int		parse_textures(char *line, t_parser *parser);
int		parse_fc(char *line, t_parser *parser);
int		open_fd(char *path);
int		parse_map(int fd, t_parser *parser);
int		parse_line_map(t_parser *parser, char *line, int *row_count);
int		check_borders(t_parser *parser);
int		parse_north(char *line, t_parser *parser);
int		parse_south(char *line, t_parser *parser);
int		parse_west(char *line, t_parser *parser);
int		parse_east(char *line, t_parser *parser);
int		parse_floor(char *line, t_parser *parser, int i, int j);
int		parse_loop(char *line, t_parser *parser, int *row_count);
void	struct_init(t_parser *parser);
int		parse_ceiling(char *line, t_parser *parser, int i, int j);
int		map_loop(char *line, int i, int j, t_parser *parser);
int		parse_orientation(char c, t_parser *parser);
void	free_parser(t_parser *parser);

void	geom_init(t_geom *geom_data, t_parser *parser);
int		create_trgb(int t, int r, int g, int b);
void	img_init(t_data *data, t_img *img_data, size_t width, size_t height);
void	texture_init(t_data *data, t_img *img, char *path);

int		red_cross(void);
void	move_forward(t_geom *geom_data);
void	move_backward(t_geom *geom_data);
void	rotate_left(t_geom *geom_data);
void	rotate_right(t_geom *geom_data);
void	strafe_left(t_geom *geom_data);
void	strafe_right(t_geom *geom_data);
int		key_hook(int keycode, t_data *data);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		check_position(t_parser *parser);

int		get_tex_color(t_img *img, int x, int y);
void	walls(t_data *data, t_geom *geom, t_img *img);
void	floor_ceiling(t_img *img, int f_color, int c_color);

void	ray_pos_dir(int x, t_geom *geom);
void	step_initial_side_dist(t_geom *geom);
void	perform_dda(t_geom *geom);
void	draw_start_end(t_geom *geom);
void	wall_x(t_geom *geom);

#endif
