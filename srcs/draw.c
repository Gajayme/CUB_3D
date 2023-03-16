/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:52:09 by georgii           #+#    #+#             */
/*   Updated: 2022/10/30 16:54:20 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_tex_color(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (4 * TEXWIDTH * y) + (4 * x)));
}

void	floor_ceiling(t_img *img, int f_color, int c_color)
{
	int	height;
	int	width;
	int	half_screen;

	height = 0;
	half_screen = SCREENHEIGHT / 2;
	while (height < SCREENHEIGHT)
	{
		width = 0;
		while (width < SCREENWIDTH)
		{
			if (height < half_screen)
				my_mlx_pixel_put(img, width, height, c_color);
			else
				my_mlx_pixel_put(img, width, height, f_color);
			width ++;
		}
		height ++;
	}
}

int	texture_picker(int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x >= 0)
			return (0);
		else
			return (1);
	}
	if (ray_dir_y > 0)
		return (2);
	else
		return (3);
}

void	walls(t_data *data, t_geom *geom, t_img *img)
{
	int	tex_num;
	int	tex_y;
	int	color;
	int	x;
	int	y;

	x = -1;
	while (++x < SCREENWIDTH)
	{
		ray_pos_dir(x, geom);
		step_initial_side_dist(geom);
		perform_dda(geom);
		draw_start_end(geom);
		wall_x(geom);
		tex_num = texture_picker(geom->side, geom->ray_dir_x, geom->ray_dir_y);
		y = geom->draw_start - 1;
		while (++y < geom->draw_end)
		{
			tex_y = (int)geom->tex_pos & (TEXHEIGHT - 1);
			geom->tex_pos += geom->step;
			color = get_tex_color(&data->tex[tex_num], geom->tex_x, tex_y);
			my_mlx_pixel_put(img, x, y, color);
		}
	}
}
