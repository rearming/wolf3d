/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:29:22 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/16 17:13:49 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			keyup_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_UP
		|| event.key.keysym.scancode == SDL_SCANCODE_W)
		wolf->actions.up = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event.key.keysym.scancode == SDL_SCANCODE_S)
		wolf->actions.down = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT
		|| event.key.keysym.scancode == SDL_SCANCODE_D)
		wolf->actions.right = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT
		|| event.key.keysym.scancode == SDL_SCANCODE_A)
		wolf->actions.left = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->actions.lshift = FALSE;
}

void			keydown_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		sdl_exit(wolf);
	if (event.key.keysym.scancode == SDL_SCANCODE_UP
		|| event.key.keysym.scancode == SDL_SCANCODE_W)
		wolf->actions.up = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event.key.keysym.scancode == SDL_SCANCODE_S)
		wolf->actions.down = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT
		|| event.key.keysym.scancode == SDL_SCANCODE_D)
		wolf->actions.right = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT
		|| event.key.keysym.scancode == SDL_SCANCODE_A)
		wolf->actions.left = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->actions.lshift = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_P)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (event.key.keysym.scancode == SDL_SCANCODE_R)
		SDL_SetRelativeMouseMode(SDL_TRUE);
}
