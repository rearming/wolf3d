/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/16 13:20:39 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		//todo add variable and easy change window resize rate (magic number 2/3/4 etc now)
		raise_error(ERR_SDL_WIN);
	if (!(sdl.rend = SDL_CreateRenderer(sdl.win, -1, 0)))
		raise_error(ERR_SDL_RENDER);
	if (!(sdl.texture = SDL_CreateTexture(sdl.rend, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (sdl);
}

void		init_keys_states(t_keys_pressed *keys_pressed)
{
	keys_pressed->down = FALSE;
	keys_pressed->up = FALSE;
	keys_pressed->left = FALSE;
	keys_pressed->right = FALSE;
	keys_pressed->lshift = FALSE;
	keys_pressed->lshift_was_pressed = FALSE;
}

void		wolf_init(t_wolf *wolf)
{
	if (wolf->map.player_spawn.x == FALSE)
		raise_error(ERR_NO_PLAYER_SPOT);
	wolf->player.x = (int)wolf->map.player_spawn.x;
	wolf->player.y = (int)wolf->map.player_spawn.y;
	wolf->player.fov = M_PI / 2; //60 градусов
	wolf->player.angle = -M_PI / 4;
	wolf->player.ang_speed = 0.001;
	wolf->player.base_speed = 0.003;
	wolf->player.fat = 4;
	wolf->minimap.scale.x = 5;
	wolf->minimap.scale.y = 10;
	wolf->render_mode = COMPASS_MODE;
	//wolf->render_mode = NUMBER_MODE;
	wolf->textures.frame = FALSE;
	wolf->player.weapon_type = GUN;
	init_keys_states(&wolf->keys_pressed);
	if (!(wolf->sdl.pixels = (int*)malloc(sizeof(int)
			* WIN_HEIGHT * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
}
