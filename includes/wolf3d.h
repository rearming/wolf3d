/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:43:10 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 13:40:27 by sleonard         ###   ########.fr       */
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
void		wolf_init(t_wolf *wolf);

/*
**	image parsing
*/

void		get_image_stbi(t_wolf *wolf, char *filename);
void		get_bmp_image(t_bmp *bmp, const char *filename);
int			get_tilemap_data(t_bmp *bmp, t_stb *stb, const char *filename);

/*
**	textures parsing
*/

t_textures	get_all_textures();

/*
**	map parsing
*/

char		**get_map(char *filename);
char		**fdf_gnl(int fd);

/*
**	render
*/

void		render(t_wolf *wolf);
t_ray raycast(t_wolf *wolf, double angle, int *color);
void		sdl_put_pixel(t_point point, t_sdl sdl);
void		bresen_line(t_wolf *wolf, t_point start, t_point end);

/*
**	render utils
*/

int 		get_int_from_rgb(int r, int g, int b);
void		get_rgb_from_int(int *r, int *g, int *b, int color);
int 		get_wall_color(int x, int y, char **map);
int 		cell_is_empty(char cell);

/*
**	minimap
*/

void		draw_minimap(t_wolf *wolf);

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

/*
**	debug
*/

void		print_bytes(t_stb image);
void print_bmp(t_bmp bmp, t_sdl sdl);
void print_texture(t_sdl sdl, int width, int height, int **data,
				   t_point print_coord);
void		print_bmp_params(t_bmp bmp);

#endif
