/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgii <georgii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:53:09 by ladrian           #+#    #+#             */
/*   Updated: 2022/10/30 15:53:03 by georgii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_parser(t_parser *parser)
{
	int	i;

	i = -1;
	free(parser->north);
	free(parser->south);
	free(parser->east);
	free(parser->west);
	if (parser->map)
	{
		while (++i < parser->map_width)
			if (parser->map[i])
				free(parser->map[i]);
		free(parser->map);
	}
}

int	open_fd(char *path)
{
	int	fd;

	if (ft_strlen(path) < 4 || !(ft_strrchr(path, '.')))
		printf("Not a cub file.\n");
	else if (ft_strncmp(ft_strrchr(path, '.'), ".cub", 4) == 0)
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			printf("Invalid directory.\n");
		return (fd);
	}
	else
		printf("Not a cub file.\n");
	return (0);
}

int	parse_line(t_parser *parser, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (parse_textures(line, parser));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (parse_fc(line, parser));
	if (*line != 0)
	{
		if (ft_strlen(line) > parser->map_width)
			parser->map_width = ft_strlen(line);
		parser->map_height += 1;
	}
	return (1);
}

int	parser_start(int fd, t_parser *parser)
{
	char	*line;
	int		ptr;

	ptr = 1;
	while (ptr > 0)
	{
		ptr = get_next_line(fd, &line);
		if (parse_line(parser, line))
			free(line);
		else
		{
			free(line);
			free_parser(parser);
			return (0);
		}
	}
	return (1);
}

int	parser_init(t_parser *parser, int argc, char **argv, int fd)
{
	if (argc != 2)
	{
		printf("Error: usage: ./Cub3d [path to the .cub file]\n");
		return (0);
	}
	fd = open_fd(argv[1]);
	if (!fd || fd == -1)
		return (0);
	struct_init(parser);
	if (!parser_start(fd, parser))
	{
		close(fd);
		return (0);
	}
	close(fd);
	fd = open_fd(argv[1]);
	if (!parse_map(fd, parser))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
