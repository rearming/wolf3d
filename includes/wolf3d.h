/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:43:10 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/19 19:42:56 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D_H
# define WOLF_3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <SDL.h>

# include "defines.h"
# include "sdb_image.h"
# include "libft.h"
# include "structs.h"
# include "colors.h"
# include "key_codes.h"
# include "errors.h"

/*
**	init
*/

t_sdl		init_sdl(void);
void		wolf_init(t_wolf *wolf);

/*
**	map parsing
*/

t_map		get_map(char *filename);
char		**fast_gnl(int fd);
int 		count_items(t_map map);
t_point		*find_items(t_wolf *wolf);

/*
**	parsing utils
*/

void 		check_player_spot(t_map *map, t_point spot);
void		check_cell(t_map *map, int x, int y);
void		check_valid(t_map *map);
int 		get_map_height(const char **char_map);
void		convert_spaces(char **map);

/*
**	image parsing
*/

void		get_image_stbi(t_wolf *wolf, char *filename);
void		get_bmp_image(t_img *bmp, const char *filename);
void		get_tilemap_data(t_img *img, const char *filename);

/*
**	textures parsing
*/

t_textures	get_all_textures();


/*
**	render
*/

void		render(t_wolf *wolf);
t_ray		raycast(t_wolf *wolf, double angle);
void		draw_column(t_ray ray, t_wolf *wolf, int win_x);

/*
**	render utils
*/

void		sdl_put_pixel(t_point point, t_sdl sdl);
void		bresen_line(t_wolf *wolf, t_point start, t_point end);
int			get_int_from_rgb(int r, int g, int b, int a);
void		get_rgb_from_int(int *r, int *g, int *b, int color);
int 		cell_is_empty(int cell);
int 		get_view_direction(t_ray ray);

/*
**	game logic utils
*/

int 		is_border_block(t_map map, t_point block);

/*
**	minimap
*/

void		draw_minimap(t_wolf *wolf);
void		draw_minimap_fov(t_wolf *wolf);
/*
**	SDL utils
*/

void		sdl_loop(t_wolf *wolf);
void		sdl_clean(t_wolf *wolf);

/*
**	hooks
*/

void		keydown_hook(t_wolf *wolf, SDL_Event event);
void		keyup_hook(t_wolf *wolf, SDL_Event event);
void		mouse_motion_hook(t_wolf *wolf, SDL_Event event);
void		mouse_down_hook(t_wolf *wolf, SDL_Event event);
void 		mouse_wheel_event(t_wolf *wolf, SDL_Event event);
void		mouse_up_hook(t_wolf *wolf, SDL_Event event);
void		mouse_actions(t_wolf *wolf);

/*
**	player's moves
*/

void		move_forward(t_wolf *wolf);
void		move_back(t_wolf *wolf);
void		move_right(t_wolf *wolf);
void		move_left(t_wolf *wolf);
void		player_run(t_wolf *wolf);

/*
**	utils
*/

void 		raise_error(int err_code);
void		sdl_exit(t_wolf *wolf);

/*
**	debug
*/

void		print_bmp_params(t_img bmp);
void		print_texture(t_sdl sdl, int width, int height,
		int **data, t_point print_coord, int bpp);

#endif
