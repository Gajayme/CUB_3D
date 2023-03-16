/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:09 by ladrian           #+#    #+#             */
/*   Updated: 2022/10/30 15:14:51 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_ceiling(char *line, t_parser *parser, int i, int j)
{
	int	num;

	if (!ft_strncmp(line, "C ", 2))
	{
		if (parser->ceiling[0] != -1000)
		{
			printf("Error: Extra C declaration!\n");
			return (0);
		}
		i = 1;
		j = -1;
		while (++j < 3)
		{
			num = 0;
			while (line[++i] && line[i] != ',')
			{
				if (line[i] != ' ')
					num *= 10;
				num += line[i] - '0';
			}
			parser->ceiling[j] = num;
		}
	}
	return (1);
}

int	parse_floor(char *line, t_parser *parser, int i, int j)
{
	int	num;

	if (!ft_strncmp(line, "F ", 2))
	{
		if (parser->floor[0] != -1000)
		{
			printf("Error: Extra F declaration!\n");
			return (0);
		}
		while (++j < 3)
		{
			num = 0;
			while (line[++i] && line[i] != ',')
			{
				if (line[i] != ' ')
					num *= 10;
				num += line[i] - '0';
			}
			parser->floor[j] = num;
		}
	}
	return (1);
}

int	parse_fc(char *line, t_parser *parser)
{
	int	i;
	int	j;
	int	num;

	i = 1;
	j = -1;
	if (!parse_floor(line, parser, i, j) || !parse_ceiling(line, parser, i, j))
		return (0);
	return (1);
}

void	struct_init(t_parser *parser)
{
	parser->map_height = 0;
	parser->map_width = 0;
	parser->floor[0] = -1000;
	parser->ceiling[0] = -1000;
	parser->north = NULL;
	parser->south = NULL;
	parser->west = NULL;
	parser->east = NULL;
	parser->x_orient = -10;
}

int	map_loop(char *line, int i, int j, t_parser *parser)
{
	if (line[i] >= 'E' && line[i] <= 'W')
	{
		parser->pos_y = i;
		parser->pos_x = j;
		if (!parse_orientation(line[i], parser))
			return (0);
		parser->map[j][i] = 0;
	}
	else if (line[i] != ' ')
		parser->map[j][i] = line[i] - '0';
	else
		parser->map[j][i] = 1;
	return (1);
}
