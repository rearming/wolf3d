/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 20:31:20 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/19 20:33:29 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		check_player_spot(t_map *map, t_point spot)
{
	int		x;
	int		y;

	y = spot.y - 1;
	x = spot.x - 1;
	while (y < spot.y + 1 && y < map->height)
	{
		x = spot.x - 1;
		while (x < spot.x + 1 && x < map->width)
		{
			if (map->int_map[y][x] != 0 && (y != spot.y || x != spot.x))
				raise_error(ERR_NO_PLAYER_SPOT);
			x++;
		}
		y++;
	}
	map->player_spawn = (t_point){x - 1, y - 1, 0, 0};
	map->int_map[y - 1][x - 1] = 0;
}

void		check_cell(t_map *map, int x, int y)
{
	if (((y == 0 || y == map->height - 1) && map->int_map[y][x] <= 0)
		|| ((x == 0 || x == map->width - 1) && map->int_map[y][x] <= 0))
	{
		map->int_map[y][x] = 1;
		return ;
	}
	if (map->int_map[y][x] > WOLF_SPRITES + MINE_SPRITES)
		map->int_map[y][x] = 1;
	if (map->int_map[y][x] == PLAYER_POS
		&& map->player_spawn.x == FALSE)
		check_player_spot(map, (t_point){x, y, 0, 0});
}

void		check_valid(t_map *map)
{
	int		x;
	int		y;

	map->player_spawn.x = FALSE;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			check_cell(map, x, y);
			x++;
		}
		y++;
	}
}

int			get_map_height(const char **char_map)
{
	int		i;

	i = 0;
	while (char_map[i])
		i++;
	return (i);
}

void		convert_spaces(char **map)
{
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				map[y][x] = '\t';
			x++;
		}
		y++;
	}
}
