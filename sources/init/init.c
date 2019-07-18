/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/18 21:49:12 by sleonard         ###   ########.fr       */
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


int 		count_items(t_map map)
{
	int 		items_nbr;
	int		 	y;
	int		 	x;

	y = 0;
	items_nbr = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] == '9')
				items_nbr++;
			x++;
		}
		y++;
	}
	return (items_nbr);
}

t_point		*find_items(t_wolf *wolf)
{
	t_point		*items;
	int		 	y;
	int		 	x;
	int 		i;

	i = 0;
	y = 0;
	wolf->map.items_nbr = count_items(wolf->map);
	if (!(items = (t_point*)malloc(sizeof(t_point) * wolf->map.items_nbr)))
		raise_error(ERR_MALLOC);
	while (y < wolf->map.height)
	{
		x = 0;
		while (x < wolf->map.width)
		{
			if (wolf->map.map[y][x] == '9')
			{
				items[i] = (t_point){x, y, 0, PICKAXE};
				i++;
			}
			x++;
		}
		y++;
	}
	return (items);
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
	wolf->player.base_speed = 0.003;
	wolf->player.fat = 4;
	wolf->minimap.scale.x = 10;
	wolf->minimap.scale.y = 10;
	wolf->render_mode = COMPASS_MODE;
	wolf->render_mode = NUMBER_MODE;
	wolf->textures.frame = 0;
	wolf->player.weapon_type = PICKAXE;
	init_actions(&wolf->actions);
	wolf->no_mouse = TRUE;
	if (!(wolf->sdl.pixels = (int*)malloc(sizeof(int)
			* WIN_HEIGHT * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
	wolf->map.items = find_items(wolf);
}
