/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:29:22 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/15 13:36:11 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			keyup_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_UP
		|| event.key.keysym.scancode == SDL_SCANCODE_W)
		wolf->keys_pressed.up = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event.key.keysym.scancode == SDL_SCANCODE_S)
		wolf->keys_pressed.down = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT
		|| event.key.keysym.scancode == SDL_SCANCODE_D)
		wolf->keys_pressed.right = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT
		|| event.key.keysym.scancode == SDL_SCANCODE_A)
		wolf->keys_pressed.left = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->keys_pressed.lshift = FALSE;
}

void			keydown_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		sdl_exit(wolf);
	if (event.key.keysym.scancode == SDL_SCANCODE_UP
		|| event.key.keysym.scancode == SDL_SCANCODE_W)
		wolf->keys_pressed.up = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event.key.keysym.scancode == SDL_SCANCODE_S)
		wolf->keys_pressed.down = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT
		|| event.key.keysym.scancode == SDL_SCANCODE_D)
		wolf->keys_pressed.right = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT
		|| event.key.keysym.scancode == SDL_SCANCODE_A)
		wolf->keys_pressed.left = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->keys_pressed.lshift = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_P)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (event.key.keysym.scancode == SDL_SCANCODE_R)
		SDL_SetRelativeMouseMode(SDL_TRUE);
}
