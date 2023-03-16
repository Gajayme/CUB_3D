/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:03:14 by georgii           #+#    #+#             */
/*   Updated: 2022/10/30 16:52:55 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_init(t_data *data, t_img *img_data, size_t width, size_t height)
{
	img_data->img = mlx_new_image(data->mlx, width, height);
	if (!img_data->img)
	{
		ft_putstr_fd("img_init\n", 2);
		exit (1);
	}
	img_data->addr = mlx_get_data_addr(img_data->img, &img_data->bits_per_pixel,
			&img_data->line_length, &img_data->endian);
}

void	geom_init(t_geom *geom_data, t_parser *parser)
{
	geom_data->parser = parser;
	geom_data->pos_x = parser->pos_x;
	geom_data->pos_y = parser->pos_y;
	geom_data->dir_x = parser->x_orient;
	geom_data->dir_y = parser->y_orient;
	geom_data->plane_x = 0.66 * (geom_data->dir_y);
	geom_data->plane_y = 0.66 * (-geom_data->dir_x);
	geom_data->move_speed = 0;
	geom_data->rot_speed = 0;
	geom_data->texture_height = TEXHEIGHT;
	geom_data->texture_width = TEXWIDTH;
}

void	texture_init(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&data->geom_data.texture_width, &data->geom_data.texture_height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->img)
	{
		ft_putstr_fd("texture_init\n", 2);
		exit (1);
	}
}
