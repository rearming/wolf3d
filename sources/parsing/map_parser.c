/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:15:10 by rearming          #+#    #+#             */
/*   Updated: 2019/08/05 21:16:47 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		split_map(t_map *map)
{
	int		x;
	int		y;

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

static void	get_int_map_cell(t_map *map, int **target,
		int *is_ended, t_point pos)
{
	if (map->raw_map[pos.y][pos.x] && !(*is_ended))
		target[pos.y][pos.x] = ft_atoi(map->raw_map[pos.y][pos.x]);
	else
	{
		*is_ended = TRUE;
		target[pos.y][pos.x] = 0;
	}
}

void		get_int_map(t_map *map, int ***target)
{
	int		x;
	int		y;
	int		is_ended;

	is_ended = FALSE;
	y = 0;
	if (!((*target) = (int**)malloc(sizeof(int*) * map->height)))
		raise_error(ERR_MALLOC);
	while (y < map->height)
	{
		x = 0;
		if (!((*target)[y] = (int*)malloc(sizeof(int*) * map->width)))
			raise_error(ERR_MALLOC);
		while (x < map->width)
		{
			get_int_map_cell(map, *target, &is_ended, (t_point){x, y, 0, 0});
			x++;
		}
		is_ended = FALSE;
		y++;
	}
}

void		clean_temp_maps(t_map *map)
{
	int		y;

	y = 0;
	while (y < map->height)
	{
		clean_chr_mtrx(map->raw_map[y]);
		y++;
	}
	free(map->raw_map);
	clean_chr_mtrx(map->char_map);
	map->raw_map = NULL;
	map->char_map = NULL;
}

t_map		get_map(char *filename)
{
	int		fd;
	t_map	map;

	fd = open(filename, O_RDONLY);
	map.char_map = NULL;
	map.int_map = NULL;
	map.backup = NULL;
	map.board = TRUE;
	map.char_map = fast_gnl(fd);
	if (!map.char_map)
		raise_error(ERR_INV_FILE);
	convert_spaces(map.char_map);
	split_map(&map);
	get_int_map(&map, &map.int_map);
	get_int_map(&map, &map.backup);
	check_valid(&map);
	clean_temp_maps(&map);
	close(fd);
	return (map);
}
