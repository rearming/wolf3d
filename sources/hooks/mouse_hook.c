/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:33:09 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/11 19:08:57 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		mouse_down_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (!cell_is_empty(wolf->map.map
			[(int) (wolf->player.y + wolf->player.speed_side
			* wolf->player.fat * sin(wolf->player.angle))]
			[(int) (wolf->player.x + wolf->player.speed_side
			* wolf->player.fat * cos(wolf->player.angle))]))
			{
				wolf->map.map[(int) (wolf->player.y + wolf->player.speed_side
				* wolf->player.fat * sin(wolf->player.angle))]
				[(int) (wolf->player.x + wolf->player.speed_side
				* wolf->player.fat * cos(wolf->player.angle))] = '0';
			}
		}
		//todo place blocks
	}
}

void		mouse_motion_hook(t_wolf *wolf, SDL_Event event)
{
	wolf->player.angle += (double)event.motion.xrel * wolf->player.ang_speed;
}
