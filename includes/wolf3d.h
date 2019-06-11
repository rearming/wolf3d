/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:43:10 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/11 19:15:01 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D_H
# define WOLF_3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <SDL.h>

# include "sdb_image.h"
# include "libft.h"
# include "structs.h"
# include "colors.h"
# include "key_codes.h"
# include "errors.h"
# include "defines.h"

/*
**	init
*/

t_sdl		init_sdl(void);

/*
**	render
*/

void		render(t_wolf *wolf);
void		sdl_put_pixel(t_wolf *wolf, t_point point);
void		bresen_line(t_wolf *wolf, t_point start, t_point end);

/*
**	SDL utils
*/

void		sdl_loop(t_wolf *wolf);
void		sdl_clean(t_wolf *wolf);

/*
**	hooks
*/

void		key_hook(t_wolf *wolf, SDL_Event event);

/*
**	utils
*/

void 		raise_error(int err_code);
void		sdl_exit(t_wolf *wolf);

#endif
