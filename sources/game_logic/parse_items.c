/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:10:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/19 20:43:05 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int 		count_items(t_map map)
{
	int 		items_nbr;
	int		 	y;
	int		 	x;

	y = 0;
	items_nbr = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.int_map[y][x] == ITEM)
				items_nbr++;
			x++;
		}
		y++;
	}
	return (items_nbr);
}

t_point		*find_items(t_wolf *wolf)
{
	t_point		*items;
	int		 	y;
	int		 	x;
	int 		i;

	i = 0;
	y = 0;
	wolf->map.items_nbr = count_items(wolf->map);
	if (!(items = (t_point*)malloc(sizeof(t_point) * wolf->map.items_nbr)))
		raise_error(ERR_MALLOC);
	while (y < wolf->map.height)
	{
		x = 0;
		while (x < wolf->map.width)
		{
			if (wolf->map.int_map[y][x] == ITEM)
			{
				items[i] = (t_point){x, y, 0, PICKAXE};
				i++;
			}
			x++;
		}
		y++;
	}
	return (items);
}
