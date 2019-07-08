/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 12:28:23 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 2", 0, 0, WIN_WIDTH * 2 , WIN_HEIGHT * 2, SDL_WINDOW_SHOWN)))
		raise_error(ERR_SDL_WIN);
	if (!(sdl.rend = SDL_CreateRenderer(sdl.win, -1, SDL_RENDERER_ACCELERATED)))
		raise_error(ERR_SDL_RENDER);
	if (!(sdl.texture = SDL_CreateTexture(sdl.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
		//todo streaming (SDL TEXTUREACCESS_STREAMING, как имейдж в mlx)
	return (sdl);
}

void		wolf_init(t_wolf *wolf)
{
	wolf->player = (t_player){3, 5, M_PI / 3, 0, 0.05};
}
