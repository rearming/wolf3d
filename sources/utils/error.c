/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:16:36 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/21 10:37:34 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 		raise_error(int err_code)
{
	ft_printf("\nError!\n");
	if (err_code == ERR_INV_ARGS)
		ft_printf("Expected two args: 1 for map (text file)"
			" and second for tilemap!\n");
	if (err_code == ERR_NO_PLAYER_SPOT)
		ft_printf("Player's spawn point ('5') must exist"
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
	if (err_code == ERR_BIG_MAP)
		ft_printf("Map is too big - size of valid maps can't be more than"
			" %i x %i chars.\n", MAX_MAP_SIZE, MAX_MAP_SIZE);
	exit(err_code);
}