/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:10:24 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/12 20:46:52 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		key_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		sdl_exit(wolf);
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		wolf->offset_x += 10;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		wolf->offset_x -= 10;
	if (event.key.keysym.scancode == SDL_SCANCODE_UP)
		wolf->offset_y -= 10;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
		wolf->offset_y += 10;
	render(wolf);
}