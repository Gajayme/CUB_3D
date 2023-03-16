/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:09 by ladrian           #+#    #+#             */
/*   Updated: 2022/10/21 17:07:19 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_east(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (parser->east)
		{
			printf("Error: Extra EA texture!\n");
			return (0);
		}
		parser->east = malloc(sizeof(line) * (ft_strlen(line) - 3));
		i = 2;
		while (line[++i])
			parser->east[i - 3] = line[i];
		parser->east[i - 3] = '\0';
	}
	return (1);
}

int	parse_west(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (parser->west)
		{
			printf("Error: Extra WE texture!\n");
			return (0);
		}
		parser->west = malloc(sizeof(line) * (ft_strlen(line) - 3));
		i = 2;
		while (line[++i])
			parser->west[i - 3] = line[i];
		parser->west[i - 3] = '\0';
	}
	return (1);
}

int	parse_south(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (parser->south)
		{
			printf("Error: Extra SO texture!\n");
			return (0);
		}
		parser->south = malloc(sizeof(line) * (ft_strlen(line) - 3));
		i = 2;
		while (line[++i])
			parser->south[i - 3] = line[i];
		parser->south[i - 3] = '\0';
	}
	return (1);
}

int	parse_north(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (parser->north)
		{
			printf("Error extra NO texture!\n");
			return (0);
		}
		parser->north = malloc(sizeof(line) * (ft_strlen(line) - 3));
		i = 2;
		while (line[++i])
			parser->north[i - 3] = line[i];
		parser->north[i - 3] = '\0';
	}
	return (1);
}

int	parse_textures(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	if (!parse_north(line, parser) || !parse_south(line, parser)
		|| !parse_west(line, parser) || !parse_east(line, parser))
		return (0);
	return (1);
}
