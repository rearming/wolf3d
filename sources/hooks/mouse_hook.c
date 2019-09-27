/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:33:09 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/27 22:21:58 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		mouse_actions(t_wolf *wolf)
{
	if (wolf->menu_flag != MENU_GAME)
		return ;
	if (wolf->actions.mouse_left
		&& (wolf->textures.weapon_frame > 4 || wolf->textures.weapon_frame == 0)
		&& wolf->player.weapon_type != PICKAXE)
		wolf->textures.weapon_frame = 1;
	if (wolf->actions.mouse_left && wolf->player.weapon_type == PICKAXE)
		break_block(wolf);
	if (wolf->actions.mouse_left == FALSE && wolf->player.weapon_type == DAKKA)
		wolf->textures.weapon_frame = 0;
}

void		mouse_up_hook(t_wolf *wolf, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		wolf->actions.mouse_left = FALSE;
	if (event->button.button == SDL_BUTTON_RIGHT)
		wolf->actions.mouse_right = FALSE;
}

void		mouse_down_hook(t_wolf *wolf, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		wolf->actions.mouse_left = TRUE;
	if (event->button.button == SDL_BUTTON_RIGHT)
	{
		place_block(wolf);
		wolf->actions.mouse_right = TRUE;
	}
}

void		mouse_motion_hook(t_wolf *wolf, SDL_Event *event)
{
	wolf->player.angle += event->motion.xrel * wolf->player.ang_speed;
	if (wolf->player.angle >= M_PI * 2)
		wolf->player.angle = 0;
	if (wolf->player.angle <= -M_PI * 2)
		wolf->player.angle = 0;
	wolf->player.look_coeff = event->motion.yrel;
	wolf->mouse_x = event->motion.x;
	wolf->mouse_y = event->motion.y;
	if (wolf->no_mouse)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		wolf->no_mouse = FALSE;
	}
}

void		mouse_wheel_event(t_wolf *wolf, SDL_Event *event)
{
	if (event->wheel.y > 0)
		wolf->player.weapon_type++;
	if (event->wheel.y < 0)
		wolf->player.weapon_type--;
	if (wolf->player.weapon_type == GUN - 1)
		wolf->player.weapon_type = WEAPONS_NUM - 1;
	else if (wolf->player.weapon_type == WEAPONS_NUM)
		wolf->player.weapon_type = GUN;
}
