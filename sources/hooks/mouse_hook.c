/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:33:09 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/15 13:36:11 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		mouse_down_hook(t_wolf *wolf, SDL_Event event)
{
	t_point			block;

	if (event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			block.x = (int)(wolf->player.x + wolf->player.speed_side
					* wolf->player.fat * cos(wolf->player.angle));
			block.y = (int)(wolf->player.y + wolf->player.speed_side
					* wolf->player.fat * sin(wolf->player.angle));
			if (!cell_is_empty(wolf->map.map[block.y][block.x])
				&& !is_border_block(wolf->map, block))
			{
				wolf->map.map[block.y][block.x] = '0';
			}
		}
		//todo 1. place blocks
		//todo 2. array-leaving protection
		//todo 3. add sound like in minecraft
	}
}

void		mouse_motion_hook(t_wolf *wolf, SDL_Event event)
{
	wolf->player.angle += (double)event.motion.xrel * wolf->player.ang_speed;
}
