/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 13:36:15 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 2", 300, 300, WIN_WIDTH * 3, WIN_HEIGHT * 3, SDL_WINDOW_SHOWN)))
		raise_error(ERR_SDL_WIN);
	if (!(sdl.rend = SDL_CreateRenderer(sdl.win, -1, SDL_RENDERER_ACCELERATED)))
		raise_error(ERR_SDL_RENDER);
	if (!(sdl.texture = SDL_CreateTexture(sdl.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
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
	printf("player's spawn: x: [%f] | y: [%f]\n", wolf->player.x, wolf->player.y);
	wolf->player.fov = M_PI / 3; //60 градусов
	wolf->player.angle = 0;
	wolf->player.speed = 0.05;
}
