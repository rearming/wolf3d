/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:15:10 by rearming          #+#    #+#             */
/*   Updated: 2019/07/25 12:59:10 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		split_map(t_map *map)
{
	int 	x;
	int 	y;

	y = 0;
	map->width = 0;
	map->height = get_map_height((const char **)map->char_map);
	if (!(map->raw_map = (char***)malloc(sizeof(char**) * map->height)))
		raise_error(ERR_MALLOC);
	while (y < map->height)
	{
		map->raw_map[y] = ft_strsplit((const char*)map->char_map[y], '\t');
		x = 0;
		while (map->raw_map[y][x])
			x++;
		map->width = x > map->width ? x : map->width;
		y++;
	}
}

void		get_int_map(t_map *map)
{
	int 	x;
	int 	y;
	int 	is_ended;

	is_ended = FALSE;
	split_map(map);
	y = 0;
	if (!(map->int_map = (int**)malloc(sizeof(int*) * map->height)))
		raise_error(ERR_MALLOC);
	while (y < map->height)
	{
		x = 0;
		if (!(map->int_map[y] = (int*)malloc(sizeof(int*) * map->width)))
			raise_error(ERR_MALLOC);
		while (x < map->width)
		{
			if (map->raw_map[y][x] && !is_ended)
				map->int_map[y][x] = ft_atoi(map->raw_map[y][x]);
			else
			{
				is_ended = TRUE;
				map->int_map[y][x] = 0;
			}
			x++;
		}
		is_ended = FALSE;
		y++;
	}
}

void		clean_temp_maps(t_map *map)
{
	int 	x;
	int 	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->raw_map[y][x])
		{
			free(map->raw_map[y][x]);
			x++;
		}
		free(map->raw_map[y]);
		y++;
	}
	free(map->raw_map);
	y = 0;
	while (map->char_map[y])
	{
		free(map->char_map[y]);
		y++;
	}
	free(map->char_map);
	map->raw_map = NULL;
	map->char_map = NULL;
}

//todo make config file with all paths to textures etc

t_map		get_map(char *filename)
{
	int 	fd;
	t_map	map;

	fd = open(filename, O_RDONLY);
	map.char_map = NULL;
	map.char_map = fast_gnl(fd);
	if (!map.char_map)
		raise_error(ERR_INV_FILE);
	convert_spaces(map.char_map);
	get_int_map(&map);
	check_valid(&map);
	clean_temp_maps(&map);
	return (map);
}
