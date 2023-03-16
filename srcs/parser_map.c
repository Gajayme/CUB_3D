/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:09 by ladrian           #+#    #+#             */
/*   Updated: 2022/10/21 17:07:19 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_borders(t_parser *parser)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	j = -1;
	flag = 1;
	while (++i < parser->map_height)
	{
		j = -1;
		while (++j < parser->map_width)
			if ((i == 0 && parser->map[i][j] == 0)
				|| (i == parser->map_height - 1 && parser->map[i][j] == 0)
				|| (j == 0 && parser->map[i][j] == 0)
				|| j == parser->map_width - 1 && parser->map[i][j] == 0)
				flag = -1;
	}
	if (flag == -1)
	{
		printf("Error: Borders are not closed!\n");
		exit(1);
	}
	return (1);
}

int	parse_orientation(char c, t_parser *parser)
{
	if (parser->x_orient >= -1 && parser->x_orient <= 1)
	{
		printf("Error: More than 1 position on the map!\n");
		exit(1);
	}
	if (c == 'N' || c == 'S')
	{
		parser->y_orient = 0;
		if (c == 'N')
			parser->x_orient = -1;
		else
			parser->x_orient = 1;
	}
	if (c == 'E' || c == 'W')
	{
		parser->x_orient = 0;
		if (c == 'E')
			parser->y_orient = 1;
		else
			parser->y_orient = -1;
	}
	return (1);
}

int	parse_line_map(t_parser *parser, char *line, int *row_count)
{
	int	i;

	i = -1;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	parser->map[*row_count] = malloc(sizeof(int) * parser->map_width);
	while (line[++i])
		if (!map_loop(line, i, *row_count, parser))
			return (0);
	i--;
	while (++i < parser->map_width)
		parser->map[*row_count][i] = 1;
	*row_count += 1;
	return (1);
}

int	parse_loop(char *line, t_parser *parser, int *row_count)
{
	if (*line != 0)
	{
		if (!parse_line_map(parser, line, row_count))
		{
			free(line);
			return (0);
		}
	}
	if (*line == 0 && *row_count > 0)
	{
		printf("Error: Empty line in the map!\n");
		exit(1);
	}
	return (1);
}

int	parse_map(int fd, t_parser *parser)
{
	char	*line;
	int		ptr;
	int		row_count;

	parser->map = malloc(sizeof(parser->map) * (parser->map_height));
	ptr = 1;
	row_count = 0;
	while (ptr > 0)
	{
		ptr = get_next_line(fd, &line);
		if (ptr && !parse_loop(line, parser, &row_count))
		{
			free_parser(parser);
			return (0);
		}
		if (line != 0)
			free(line);
	}
	if (!check_borders(parser) || !check_position(parser))
	{
		free_parser(parser);
		return (0);
	}
	return (1);
}
