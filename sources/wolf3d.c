/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:42:56 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/28 12:34:10 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "wolf3d.h"

int 		main(int argc, char **argv)
{
	t_wolf		wolf;
	char 		**config_args;


	config_args = parse_params(argv, argc);
	wolf.map = get_map(argv[1]);
	wolf.sdl = init_sdl();
	wolf.ttf = init_ttf(config_args[CONFIG_SIZE - 1]);
	wolf.textures = get_all_textures((const char **)config_args);
	wolf_init(&wolf);
	render(&wolf);
	sdl_loop(&wolf);
	return (0);
}
