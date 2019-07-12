/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:15:10 by rearming          #+#    #+#             */
/*   Updated: 2019/07/12 14:04:49 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		check_cell(t_map *map, int x, int y, int outer)
{
	if (!ft_isdigit(map->map[y][x]))
		map->map[y][x] = '1';
	if (outer)
	{
		if (map->map[y][0] == ' ' || map->map[y][0] == '0'
			|| map->map[y][0] == '5')
			map->map[y][0] = '1';
		if (map->map[y][map->width] == ' ' || map->map[y][map->width] == '0'
			|| map->map[y][map->width] == '5')
			map->map[y][map->width] = '1';
	}
	else
	{
		if (map->map[0][x] == ' ' || map->map[0][x] == '0'
			|| map->map[0][x] == '5')
			map->map[0][x] = '1';
		if (map->map[map->height - 1][x] == ' '
			|| map->map[map->height - 1][x] == '0'
			|| map->map[map->height - 1][x] == '5')
			map->map[map->height - 1][x] = '1';
		if (map->map[y][x] == '5' && map->player_spawn.x == FALSE
		&& !is_border_block(*map, (t_point){x, y}))
			map->player_spawn = (t_point){x, y, 0, 0};
	}
}

void		check_valid(t_map *map)
{
	int 	x;
	int 	y;

	map->player_spawn.x = FALSE;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		check_cell(map, x, y, TRUE);
		while (x < map->width)
		{
			check_cell(map, x, y, FALSE);
			x++;
		}
		y++;
	}
}

void		convert_map(t_map *raw_map)
{
	char 	**map;
	int 	i;

	if (!(map = (char**)malloc(sizeof(char*) * raw_map->height)))
		raise_error(ERR_MALLOC);
	map[raw_map->height] = 0;
	i = 0;
	while (i < raw_map->height)
	{
		if (!(map[i] = (char*)malloc(sizeof(char) * (raw_map->width + 1))))
			raise_error(ERR_MALLOC);
		ft_memset(map[i], '1', raw_map->width);
		map[i][raw_map->width] = 0;
		ft_memcpy(map[i], raw_map->map[i], ft_strlen(raw_map->map[i]));
		free(raw_map->map[i]);
		i++;
	}
	free(raw_map->map);
	raw_map->map = map;
}

void		get_map_params(t_map *raw_map)
{
	int		line;
	int 	line_len;
	int 	max_line_len;

	line = 0;
	max_line_len = 0;
	while (raw_map->map[line])
	{
		line_len = ft_strlen(raw_map->map[line]);
		max_line_len = line_len > max_line_len ? line_len : max_line_len;
		line++;
	}
	raw_map->width = max_line_len;
	raw_map->height = line;
}

t_map		get_map(char *filename)
{
	int 	fd;
	t_map	map;

	fd = open(filename, O_RDONLY);
	map.map = fast_gnl(fd);
	get_map_params(&map);
	convert_map(&map);
	check_valid(&map);
	return (map);
}
