/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 21:54:50 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 21:21:05 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	check_index(int texture_type, int index)
{
	if (index > 0)
	{
		if (texture_type == MINECRAFT && index >= MINE_SPRITES)
			return (0);
		else if (texture_type == WOLF3D && index >= WOLF_SPRITES)
			return (0);
		else
			return (1);
	}
	return (0);
}

void		change_block_index(t_wolf *wolf, t_erm *term)
{
	t_ray	ray;
	int		index;

	ray = raycast(wolf, wolf->player.angle);
	index = term->parsed_command[2];
	if (check_index(wolf->textures.texture_type, index))
		wolf->map.int_map[(int)ray.y][(int)ray.x] = term->parsed_command[2];
}

int			switch_int_maps(t_map *map, t_erm *term)
{
	int		**temp;

	if (term->parsed_command[2] == DEFAULT)
	{
		temp = map->backup;
		map->backup = map->int_map;
		map->int_map = temp;
		map->board = FALSE;
		return (0);
	}
	else if (map->board == FALSE)
	{
		temp = map->backup;
		map->backup = map->int_map;
		map->int_map = temp;
		map->board = TRUE;
	}
	return (1);
}

void		change_all_blocks(t_wolf *wolf, t_erm *term)
{
	int		y;
	int		x;
	int		index;

	if (!switch_int_maps(&wolf->map, term))
		return ;
	index = term->parsed_command[2];
	if (!check_index(wolf->textures.texture_type, index))
		return ;
	y = 0;
	while (y < wolf->map.height)
	{
		x = 0;
		while (x < wolf->map.width)
		{
			if (wolf->map.int_map[y][x] > 0)
				wolf->map.int_map[y][x] = term->parsed_command[2];
			x++;
		}
		y++;
	}
}
