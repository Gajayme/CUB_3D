/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:56:13 by lyubov            #+#    #+#             */
/*   Updated: 2022/10/30 16:52:19 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <time.h>

int	render_next_frame(t_data *data)
{
	clock_t	start_t;
	double	frame_time;
	double	frame_time_sec;

	start_t = clock();
	img_init(data, &data->img_data, SCREENWIDTH, SCREENHEIGHT);
	floor_ceiling(&data->img_data, data->floor_color, data->ceiling_color);
	walls(data, &data->geom_data, &data->img_data);
	frame_time = (clock() - start_t);
	frame_time_sec = frame_time / CLOCKS_PER_SEC;
	data->geom_data.move_speed = frame_time_sec * 150;
	data->geom_data.rot_speed = frame_time_sec * 100;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img_data.img);
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*path;
	t_data		data;
	t_parser	parser;

	if (!parser_init(&parser, argc, argv, fd))
		return (0);
	data.mlx = mlx_init();
	data.ceiling_color = create_trgb(0, parser.ceiling[0], \
							parser.ceiling[1], parser.ceiling[2]);
	data.floor_color = create_trgb(0, parser.floor[0], \
							parser.floor[1], parser.floor[2]);
	data.mlx_win = mlx_new_window(data.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	geom_init(&data.geom_data, &parser);
	texture_init(&data, &data.tex[0], parser.south);
	texture_init(&data, &data.tex[1], parser.north);
	texture_init(&data, &data.tex[2], parser.east);
	texture_init(&data, &data.tex[3], parser.west);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.mlx_win, 17, 0, red_cross, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	free_parser(&parser);
	exit(0);
}
