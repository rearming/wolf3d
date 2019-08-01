/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:06:46 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/01 14:13:06 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	player_moving(t_wolf *wolf)
{
	if (wolf->actions.up)
		move_forward(wolf);
	if (wolf->actions.down)
		move_back(wolf);
	if (wolf->actions.right)
		move_right(wolf);
	if (wolf->actions.left)
		move_left(wolf);
	if (wolf->actions.arr_left)
		wolf->player.angle -= 0.05;
	if (wolf->actions.arr_right)
		wolf->player.angle += 0.05;
	player_run(wolf);
}

static int	get_tickrate(t_wolf *wolf)
{
	uint32_t		tick;

	tick = SDL_GetTicks();
	render(wolf);
	tick = SDL_GetTicks() - tick;
	return (tick);
}

void		process_event(SDL_Event *event, t_wolf *wolf)
{
	if (event->type == SDL_KEYDOWN)
		keydown_hook(wolf, event);
	if (wolf->term.opened)
		return ;
	if (event->type == SDL_MOUSEWHEEL)
		mouse_wheel_event(wolf, event);
	if (event->type == SDL_KEYUP)
		keyup_hook(wolf, event);
	if (event->type == SDL_MOUSEMOTION)
		mouse_motion_hook(wolf, event);
	if (event->type == SDL_MOUSEBUTTONDOWN)
		mouse_down_hook(wolf, event);
	if (event->type == SDL_MOUSEBUTTONUP)
		mouse_up_hook(wolf, event);
}

void		sdl_loop(t_wolf *wolf)
{
	SDL_Event		event;
	double			ticks;

	ticks = 0;
	while (21)
	{
		while (SDL_PollEvent(&event))
			process_event(&event, wolf);
		if (event.type == SDL_QUIT)
			break ;
		wolf->tickrate = get_tickrate(wolf);
		ticks += wolf->tickrate;
		if (ticks >= POS_UPDATE)
		{
			player_moving(wolf);
			ticks = 0;
		}
		mouse_actions(wolf);
	}
}
