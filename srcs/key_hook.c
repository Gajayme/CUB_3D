/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:10:56 by lyubov            #+#    #+#             */
/*   Updated: 2022/10/30 16:47:24 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	red_cross(void)
{
	exit (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 13)
		move_forward(&data->geom_data);
	if (keycode == 1)
		move_backward(&data->geom_data);
	if (keycode == 123)
		rotate_left(&data->geom_data);
	if (keycode == 124)
		rotate_right(&data->geom_data);
	if (keycode == 0)
		strafe_left(&data->geom_data);
	if (keycode == 2)
		strafe_right(&data->geom_data);
	if (keycode == 53)
		exit (0);
	return (0);
}

void	strafe_right(t_geom *geom_data)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = geom_data->dir_y;
	tmp_y = -geom_data->dir_x;
	if (geom_data->parser->map[(int)(geom_data->pos_x + tmp_x
			* geom_data->move_speed)][(int)geom_data->pos_y] == 0)
	{
		geom_data->pos_x += tmp_x * geom_data->move_speed;
	}
	if (geom_data->parser->map[(int)geom_data->pos_x][(int)(geom_data->pos_y
		+ tmp_y * geom_data->move_speed)] == 0)
	{
		geom_data->pos_y += tmp_y * geom_data->move_speed;
	}
}

void	strafe_left(t_geom *geom_data)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = -geom_data->dir_y;
	tmp_y = geom_data->dir_x;
	if (geom_data->parser->map[(int)(geom_data->pos_x + tmp_x
			* geom_data->move_speed)][(int)geom_data->pos_y] == 0)
	{
		geom_data->pos_x += tmp_x * geom_data->move_speed;
	}
	if (geom_data->parser->map[(int)geom_data->pos_x][(int)(geom_data->pos_y
		+ tmp_y * geom_data->move_speed)] == 0)
	{
		geom_data->pos_y += tmp_y * geom_data->move_speed;
	}
}
