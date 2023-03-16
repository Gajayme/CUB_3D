/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:53:09 by georgii           #+#    #+#             */
/*   Updated: 2022/10/24 21:58:58 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <math.h>

void	move_forward(t_geom *geom_data)
{
	if (geom_data->parser->map[(int)(geom_data->pos_x + geom_data->dir_x
			* geom_data->move_speed)][(int)geom_data->pos_y] == 0)
	{
		geom_data->pos_x += geom_data->dir_x * geom_data->move_speed;
	}
	if (geom_data->parser->map[(int)geom_data->pos_x][(int)(geom_data->pos_y
		+ geom_data->dir_y * geom_data->move_speed)] == 0)
	{
		geom_data->pos_y += geom_data->dir_y * geom_data->move_speed;
	}
}

void	move_backward(t_geom *geom_data)
{
	if (geom_data->parser->map[(int)(geom_data->pos_x - geom_data->dir_x
			* geom_data->move_speed)][(int)geom_data->pos_y] == 0)
	{
		geom_data->pos_x -= geom_data->dir_x * geom_data->move_speed;
	}
	if (geom_data->parser->map[(int)geom_data->pos_x][(int)(geom_data->pos_y
		- geom_data->dir_y * geom_data->move_speed)] == 0)
	{
		geom_data->pos_y -= geom_data->dir_y * geom_data->move_speed;
	}
}

void	rotate_left(t_geom *geom_data)
{
	double	old_dir_x;
	double	oldplane_x;

	old_dir_x = geom_data->dir_x;
	geom_data->dir_x = geom_data->dir_x * cos(geom_data->rot_speed)
		- geom_data->dir_y * sin(geom_data->rot_speed);
	geom_data->dir_y = old_dir_x * sin(geom_data->rot_speed)
		+ geom_data->dir_y * cos(geom_data->rot_speed);
	oldplane_x = geom_data->plane_x;
	geom_data->plane_x = geom_data->plane_x * cos(geom_data->rot_speed)
		- geom_data->plane_y * sin(geom_data->rot_speed);
	geom_data->plane_y = oldplane_x * sin(geom_data->rot_speed)
		+ geom_data->plane_y * cos(geom_data->rot_speed);
}

void	rotate_right(t_geom *geom_data)
{
	double	old_dir_x;
	double	oldplane_x;

	old_dir_x = geom_data->dir_x;
	geom_data->dir_x = geom_data->dir_x * cos(-geom_data->rot_speed)
		- geom_data->dir_y * sin(-geom_data->rot_speed);
	geom_data->dir_y = old_dir_x * sin(-geom_data->rot_speed)
		+ geom_data->dir_y * cos(-geom_data->rot_speed);
	oldplane_x = geom_data->plane_x;
	geom_data->plane_x = geom_data->plane_x * cos(-geom_data->rot_speed)
		- geom_data->plane_y * sin(-geom_data->rot_speed);
	geom_data->plane_y = oldplane_x * sin(-geom_data->rot_speed)
		+ geom_data->plane_y * cos(-geom_data->rot_speed);
}
