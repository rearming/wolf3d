/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:10:24 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 14:49:28 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		key_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		sdl_exit(wolf);
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT || event.key.keysym.sym == SDLK_d)
	{
		if (cell_is_empty(wolf->map
		[(int)(wolf->player.y + wolf->player.speed_side * wolf->player.fat * sin(wolf->player.angle + M_PI / 2))]
		[(int)(wolf->player.x + wolf->player.speed_side * wolf->player.fat * cos(wolf->player.angle + M_PI / 2))]))
		{
			wolf->player.y += wolf->player.speed_side * sin(wolf->player.angle + M_PI / 2);
			wolf->player.x += wolf->player.speed_side * cos(wolf->player.angle + M_PI / 2);
		}
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT || event.key.keysym.sym == SDLK_a)
	{
		if (cell_is_empty(wolf->map
		[(int)(wolf->player.y + wolf->player.speed_side * wolf->player.fat * sin(wolf->player.angle - M_PI / 2))]
		[(int)(wolf->player.x + wolf->player.speed_side * wolf->player.fat * cos(wolf->player.angle - M_PI / 2))]))
		{
			wolf->player.y += wolf->player.speed_side * sin(wolf->player.angle - M_PI / 2);
			wolf->player.x += wolf->player.speed_side * cos(wolf->player.angle - M_PI / 2);
		}
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_UP || event.key.keysym.sym == SDLK_w)
	{
		if (cell_is_empty(wolf->map
		[(int)(wolf->player.y + wolf->player.speed_side * wolf->player.fat * sin(wolf->player.angle))]
		[(int)(wolf->player.x + wolf->player.speed_side * wolf->player.fat * cos(wolf->player.angle))]))
		{
			wolf->player.y += wolf->player.speed_fwd * sin(wolf->player.angle);
			wolf->player.x += wolf->player.speed_fwd * cos(wolf->player.angle);
		}
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN || event.key.keysym.sym == SDLK_s)
	{
		if (cell_is_empty(wolf->map
		[(int)(wolf->player.y - wolf->player.speed_side * wolf->player.fat * sin(wolf->player.angle))]
		[(int)(wolf->player.x - wolf->player.speed_side * wolf->player.fat * cos(wolf->player.angle))]))
		{
			wolf->player.y -= wolf->player.speed_fwd * sin(wolf->player.angle);
			wolf->player.x -= wolf->player.speed_fwd * cos(wolf->player.angle);
		}
	}
}
