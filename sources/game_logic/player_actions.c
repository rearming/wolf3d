/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:44:15 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/01 19:08:51 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		break_block(t_wolf *wolf)
{
	t_point		block;

	block.x = (int)(wolf->player.x + wolf->player.speed_side
			* wolf->player.fat * cos(wolf->player.angle));
	block.y = (int)(wolf->player.y + wolf->player.speed_side
			* wolf->player.fat * sin(wolf->player.angle));
	if (!cell_is_empty(wolf->map, block)
		&& !is_border_block(wolf->map, block))
		wolf->map.int_map[block.y][block.x] = 0;
}

void		place_block(t_wolf *wolf)
{
	t_ray		ray;

	if (wolf->player.weapon_type != PICKAXE)
		return ;
	ray = raycast(wolf, wolf->player.angle);
	if (ray.distance > 4 || ray.distance < 2)
		return ;
	if (ray.direction == VIEW_RIGHT)
		wolf->map.int_map[(int)ray.y][(int)ray.x - 1] = 1;
	if (ray.direction == VIEW_LEFT)
		wolf->map.int_map[(int)ray.y][(int)ray.x + 1] = 2;
	if (ray.direction == VIEW_DOWN)
		wolf->map.int_map[(int)ray.y - 1][(int)ray.x] = 3;
	if (ray.direction == VIEW_UP)
		wolf->map.int_map[(int)ray.y + 1][(int)ray.x] = 4;
}
