/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:42:56 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 18:20:04 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "wolf3d.h"

int 		main(int argc, char **argv)
{
	t_wolf		wolf;

	if (argc < 2)
		raise_error(ERR_INV_ARGS);
	wolf.sdl = init_sdl();
	wolf_init(&wolf);
	wolf.map = get_map(argv[1]);
	wolf.stb.filename = argv[2];
	get_image_data(&wolf);


	//todo get all needed textures
	/*t_stb	stb;

	stb.width = 64;
	stb.heigth = 64;
	stb.bpp = wolf->stb.bpp;
	stb.sprite = get_sprite(wolf->stb.data, wolf->stb.width, wolf->stb.bpp, wolf->sdl);
	print_image(stb, wolf->sdl);*/

	render(&wolf);
	sdl_loop(&wolf);
	return (0);
}