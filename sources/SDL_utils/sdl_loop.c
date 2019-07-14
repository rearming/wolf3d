/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:06:46 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/14 16:20:12 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		player_moving(t_wolf *wolf)
{
	if (wolf->keys_pressed.up)
		move_forward(wolf);
	if (wolf->keys_pressed.down)
		move_back(wolf);
	if (wolf->keys_pressed.right)
		move_right(wolf);
	if (wolf->keys_pressed.left)
		move_left(wolf);
	player_run(wolf);
}

void		sdl_loop(t_wolf *wolf)
{
	SDL_Event		event;

	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
				keydown_hook(wolf, event);
			if (event.type == SDL_KEYUP)
				keyup_hook(wolf, event);
			if (event.type == SDL_MOUSEMOTION)
				mouse_motion_hook(wolf, event);
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mouse_down_hook(wolf, event);
		}
		if (event.type == SDL_QUIT)
			break ;
		player_moving(wolf);
		uint32_t start = SDL_GetTicks(); //todo run depend on render time !
		render(wolf);
		printf("render time: [%i]\n", SDL_GetTicks() - start);
	}
}
