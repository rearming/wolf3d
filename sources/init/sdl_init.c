/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 20:36:57 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/01 16:03:32 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 3",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		raise_error(ERR_SDL_WIN);
	if (!(sdl.rend = SDL_CreateRenderer(sdl.win, -1, SDL_RENDERER_SOFTWARE)))
		raise_error(ERR_SDL_RENDER);
	if (!(sdl.texture = SDL_CreateTexture(sdl.rend, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
	return (sdl);
}

t_ttf		init_ttf(char *font_file)
{
	t_ttf	ttf;
	int		ret;

	ttf.font = NULL;
	ret = TTF_Init();
	if (ret == TTF_ERROR)
		raise_error(ERR_SDL_TTF_INIT);
	if (!(ttf.font = TTF_OpenFont(font_file, 500)))
		raise_error(ERR_SDL_TTF_OPENFONT);
	return (ttf);
}
