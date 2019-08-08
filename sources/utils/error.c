/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:16:36 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/08 14:25:22 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	raise_error2(int err_code)
{
	if (err_code == ERR_BIG_MAP)
		ft_printf("Map is too big - size of valid maps can't be more than"
				" %i x %i chars.\n", MAX_MAP_SIZE, MAX_MAP_SIZE);
	if (err_code == ERR_INV_IMAGE)
		ft_printf("Image or texture file is invalid for some reason!\n");
	if (err_code == ERR_INV_CONFIG_SIZE)
		ft_printf("Invalid config file, expected %i strings\n", CONFIG_SIZE);
	if (err_code == ERR_SDL_INIT)
		ft_printf("SDL ttf error: %s\n", "TTF_Init failed.");
	if (err_code == ERR_SDL_TTF_OPENFONT)
		ft_printf("SDL ttf error: %s\n", "can't open font file.");
	if (err_code == ERR_SDL_TTF_RENDERTEXT)
		ft_printf("SDL ttf error: %s\n", "TTF_RenderText failed.");
	if (err_code == ERR_INV_TEXTURE_TABLE)
		ft_printf("Invalid wolf_ignore.wolf file\n");
}

void		raise_error(int err_code)
{
	ft_printf("\nError!\n");
	if (err_code == ERR_INV_ARGS)
		ft_printf("Expected two args: first for map (text file)"
			" and second for \"wolf_config.wolf\" file.\n");
	if (err_code == ERR_NO_PLAYER_SPOT)
		ft_printf("Player's spawn point ('-1') must exist"
			" and be inside the map, surrounded by empty cells!\n");
	if (err_code == ERR_INV_MAP_SYMBOL)
		ft_printf("Valid maps must contain only numbers.\n");
	if (err_code == ERR_INV_FILE)
		ft_printf("File is invalid!\n");
	if (err_code == ERR_MALLOC)
		ft_printf("Wtf? malloc() failed.\n");
	if (err_code == ERR_SDL_INIT)
		ft_printf("SDL_Init failed.\n");
	if (err_code == ERR_SDL_WIN)
		ft_printf("SDL_Create_Window failed.\n");
	if (err_code == ERR_SDL_RENDER)
		ft_printf("SDL_Create_Renderer failed.\n");
	if (err_code == ERR_SDL_TEXTURE_CREATE)
		ft_printf("SDL_Create_Texture failed.\n");
	raise_error2(err_code);
	exit(err_code);
}
