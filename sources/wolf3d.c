/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:42:56 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/11 19:38:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "wolf3d.h"

int 		main(int argc, char **argv)
{
	t_wolf		wolf;

	if (argc != 2)
		raise_error(ERR_INV_ARGS);
	wolf.sdl = init_sdl();
	render(&wolf);
	sdl_loop(&wolf);
	return (0);
}