/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/20 19:53:36 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		raise_error(ERR_SDL_WIN);
	if (!(sdl.rend = SDL_CreateRenderer(sdl.win, -1, 0)))
		raise_error(ERR_SDL_RENDER);
	if (!(sdl.texture = SDL_CreateTexture(sdl.rend, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
	return (sdl);
}

void		init_actions(t_actions *actions)
{
	actions->down = FALSE;
	actions->up = FALSE;
	actions->left = FALSE;
	actions->right = FALSE;
	actions->lshift = FALSE;
	actions->lshift_was_pressed = FALSE;
	actions->mouse_right = FALSE;
	actions->mouse_left = FALSE;
}

void		wolf_init(t_wolf *wolf)
{
	if (wolf->map.player_spawn.x == FALSE)
		raise_error(ERR_NO_PLAYER_SPOT);
	wolf->player.x = (int)wolf->map.player_spawn.x;
	wolf->player.y = (int)wolf->map.player_spawn.y;
	wolf->player.fov = M_PI / 2; // pi / 3 = 60 градусов, pi / 2 = 90
	wolf->player.angle = 0;
	wolf->player.ang_speed = 0.001;
	wolf->player.speed_fwd = 0.3;
	wolf->player.speed_side = 0.15;
	wolf->player.fat = 3;

	wolf->minimap.fov_scale = 10;
	wolf->minimap.scale.x = 300;
	wolf->minimap.scale.y = 300;
	wolf->minimap.size.x = 30;
	wolf->minimap.size.y = 30;

	//todo get this info from args
	//wolf->textures.render_mode = COMPASS_MODE;
	wolf->textures.render_mode = NUMBER_MODE;
	//wolf->textures.texture_mode = MINECRAFT;
	wolf->textures.texture_mode = WOLF3D;

	wolf->textures.frame = 1;
	wolf->textures.w_frame = 0;
	wolf->player.weapon_type = PICKAXE;
	init_actions(&wolf->actions);
	wolf->no_mouse = TRUE;
	if (!(wolf->sdl.pixels = (int*)malloc(sizeof(int)
			* WIN_HEIGHT * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
	wolf->map.items = find_items(wolf);
}
