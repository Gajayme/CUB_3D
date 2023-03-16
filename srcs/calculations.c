/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:45:46 by georgii           #+#    #+#             */
/*   Updated: 2022/10/30 16:55:19 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

void	ray_pos_dir(int x, t_geom *geom)
{
	geom->camera_x = 2 * (x / (double)SCREENWIDTH) - 1;
	geom->ray_dir_x = geom->dir_x + geom->plane_x * geom->camera_x;
	geom->ray_dir_y = geom->dir_y + geom->plane_y * geom->camera_x;
	geom->map_x = (int)geom->pos_x;
	geom->map_y = (int)geom->pos_y;
	if (geom->ray_dir_x == 0)
		geom->delta_dist_x = 1e30;
	else
		geom->delta_dist_x = fabs(1 / geom->ray_dir_x);
	if (geom->ray_dir_y == 0)
		geom->delta_dist_y = 1e30;
	else
		geom->delta_dist_y = fabs(1 / geom->ray_dir_y);
	geom->hit = 0;
}

void	step_initial_side_dist(t_geom *geom)
{
	if (geom->ray_dir_x < 0)
	{
		geom->step_x = -1;
		geom->side_dist_x = (geom->pos_x - geom->map_x) * geom->delta_dist_x;
	}
	else
	{
		geom->step_x = 1;
		geom->side_dist_x = (geom->map_x + 1.0 - geom->pos_x)
			* geom->delta_dist_x;
	}
	if (geom->ray_dir_y < 0)
	{
		geom->step_y = -1;
		geom->side_dist_y = (geom->pos_y - geom->map_y) * geom->delta_dist_y;
	}
	else
	{
		geom->step_y = 1;
		geom->side_dist_y = (geom->map_y + 1.0 - geom->pos_y)
			* geom->delta_dist_y;
	}
}

void	perform_dda(t_geom *geom)
{
	while (geom->hit == 0)
	{
		if (geom->side_dist_x < geom->side_dist_y)
		{
			geom->side_dist_x += geom->delta_dist_x;
			geom->map_x += geom->step_x;
			geom->side = 0;
		}
		else
		{
			geom->side_dist_y += geom->delta_dist_y;
			geom->map_y += geom->step_y;
			geom->side = 1;
		}
		if (geom->parser->map[geom->map_x][geom->map_y] > 0)
			geom->hit = 1;
	}
	if (geom->side == 0)
		geom->perp_wall_dist = (geom->side_dist_x - geom->delta_dist_x);
	else
		geom->perp_wall_dist = (geom->side_dist_y - geom->delta_dist_y);
}

void	draw_start_end(t_geom *geom)
{
	geom->line_height = (int)(SCREENHEIGHT / geom->perp_wall_dist);
	geom->draw_start = -geom->line_height / 2 + SCREENHEIGHT / 2;
	if (geom->draw_start < 0)
		geom->draw_start = 0;
	geom->draw_end = geom->line_height / 2 + SCREENHEIGHT / 2;
	if (geom->draw_end >= SCREENHEIGHT)
		geom->draw_end = SCREENHEIGHT - 1;
}

void	wall_x(t_geom *geom)
{
	if (geom->side == 0)
		geom->wall_x = geom->pos_y + geom->perp_wall_dist * geom->ray_dir_y;
	else
		geom->wall_x = geom->pos_x + geom->perp_wall_dist * geom->ray_dir_x;
	geom->wall_x -= floor((geom->wall_x));
	geom->tex_x = (int)(geom->wall_x * (double)(geom->texture_width));
	if (geom->side == 0 && geom->ray_dir_x > 0)
		geom->tex_x = geom->texture_width - geom->tex_x - 1;
	if (geom->side == 1 && geom->ray_dir_y < 0)
		geom->tex_x = geom->texture_width - geom->tex_x - 1;
	geom->step = 1.0 * geom->texture_height / geom->line_height;
	geom->tex_pos = (geom->draw_start - SCREENHEIGHT / 2
			+ geom->line_height / 2) * geom->step;
}
