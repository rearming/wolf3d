/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:10:24 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 12:30:12 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		key_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		sdl_exit(wolf);
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		wolf->player.angle -= 0.02;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		wolf->player.angle += 0.02;
	if (event.key.keysym.scancode == SDL_SCANCODE_UP)
	{
		wolf->player.y += 0.05 * sin(wolf->player.angle);
		printf("sin: [%f] | cos: [%f]\n", sin(wolf->player.angle), cos(wolf->player.angle));
		wolf->player.x += 0.05 * cos(wolf->player.angle);
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
	{
		wolf->player.y -= 0.05 * sin(wolf->player.angle);
		printf("sin: [%f] | cos: [%f]\n", sin(wolf->player.angle), cos(wolf->player.angle));
		wolf->player.x -= 0.05 * cos(wolf->player.angle);
	}
}