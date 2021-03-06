/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:29:22 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/27 21:27:56 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			keyup_hook(t_wolf *wolf, SDL_Event *event)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_UP
		|| event->key.keysym.scancode == SDL_SCANCODE_W)
		wolf->actions.up = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event->key.keysym.scancode == SDL_SCANCODE_S)
		wolf->actions.down = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT
		|| event->key.keysym.scancode == SDL_SCANCODE_D)
		wolf->actions.right = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_LEFT
		|| event->key.keysym.scancode == SDL_SCANCODE_A)
		wolf->actions.left = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->actions.lshift = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		wolf->actions.arr_right = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		wolf->actions.arr_left = FALSE;
	if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
		wolf->actions.space = FALSE;
}

void			keydown_hook2(t_wolf *wolf, SDL_Event *event)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
		wolf->actions.space = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		if (wolf->menu_flag == MENU_MAIN)
			sdl_exit(wolf);
		else if (wolf->menu_flag == MENU_GAME
			|| wolf->menu_flag == MENU_CONTROLS
			|| wolf->menu_flag == MENU_MAPS)
		{
			if (wolf->menu_flag == MENU_GAME && !wolf->flag_two)
				wolf->flag_two = 1;
			wolf->menu_flag = MENU_MAIN;
		}
		else
			wolf->menu_flag = MENU_CONTROLS;
	}
}

void			keydown_hook(t_wolf *wolf, SDL_Event *event)
{
	if (check_term(wolf, event->key.keysym))
		return (get_term_input(wolf, event->key.keysym));
	if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		wolf->actions.arr_right = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		wolf->actions.arr_left = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_UP
		|| event->key.keysym.scancode == SDL_SCANCODE_W)
		wolf->actions.up = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event->key.keysym.scancode == SDL_SCANCODE_S)
		wolf->actions.down = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_D)
		wolf->actions.right = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_A)
		wolf->actions.left = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->actions.lshift = TRUE;
	if (event->key.keysym.scancode == SDL_SCANCODE_P)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (event->key.keysym.scancode == SDL_SCANCODE_R)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	keydown_hook2(wolf, event);
}
