/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 19:25:08 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * 2, WIN_HEIGHT * 2, SDL_WINDOW_OPENGL)))
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

void		get_player_position(char **map, double *ret_x, double *ret_y)
{
	int		x;
	int 	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == PLAYER_POS)
				break ;
			x++;
		}
		if (map[y][x] == PLAYER_POS)
			break;
		y++;
	}
	*ret_x = (double)x;
	*ret_y = (double)y;
}

void		wolf_init(t_wolf *wolf)
{
	get_player_position(wolf->map, &wolf->player.x, &wolf->player.y);
	wolf->player.fov = M_PI / 3; //60 градусов
	wolf->player.angle = 0;
	wolf->player.ang_speed = 0.05;
	wolf->player.speed_fwd = 0.3;
	wolf->player.speed_side = 0.2;
	wolf->player.fat = 2.5;
	wolf->minimap.scale.x = 3;
	wolf->minimap.scale.y = 6;
	wolf->render_mode = COMPASS_MODE;
	//wolf->render_mode = NUMBER_MODE;
	if (!(wolf->sdl.pixels = (int*)malloc(sizeof(int) * WIN_HEIGHT * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
}
