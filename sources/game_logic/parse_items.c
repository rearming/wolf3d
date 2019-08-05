/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:10:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 12:17:16 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			count_items(t_map *map)
{
	int			items_nbr;
	int			y;
	int			x;

	y = 0;
	items_nbr = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->int_map[y][x] == ITEM)
				items_nbr++;
			x++;
		}
		y++;
	}
	return (items_nbr);
}

t_point		*find_items(t_map *map)
{
	t_point		*items;
	t_point		p;
	int			i;

	i = 0;
	p.y = 0;
	map->items_nbr = count_items(map);
	if (!(items = (t_point*)malloc(sizeof(t_point) * map->items_nbr)))
		raise_error(ERR_MALLOC);
	while (p.y < map->height)
	{
		p.x = 0;
		while (p.x < map->width)
		{
			if (map->int_map[p.y][p.x] != PLAYER_POS
			&& map->int_map[p.y][p.x] < 0)
			{
				items[i] = (t_point){p.x, p.y, 0, map->int_map[p.y][p.x]};
				i++;
			}
			p.x++;
		}
		p.y++;
	}
	return (items);
}
