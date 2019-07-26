/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:43:10 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 14:54:55 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D_H
# define WOLF_3D_H

# include "../SDL2_libs/SDL2/src/video/SDL_pixels_c.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL2/SDL_ttf.h>

# include "sdb_image.h"
# include "libft.h"
# include "defines.h"
# include "term_defines.h"
# include "structs.h"
# include "colors.h"
# include "errors.h"

/*
**	init
*/

t_sdl		init_sdl(void);
t_ttf		init_ttf(char *font_file);
void		wolf_init(t_wolf *wolf);

/*
**	params parsing
*/

char **parse_params(char **argv, int argc);

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

t_textures get_all_textures(const char **files);

/*
**	render
*/

void		render(t_wolf *wolf);
t_ray		raycast(t_wolf *wolf, double angle);
void		draw_column(t_ray *ray, t_wolf *wolf, int win_x);
void		scaled_draw(t_sdl sdl, t_sprite sprite,
					double scale, t_point print_coord);
void		draw_animated(double *frame, int tickrate,
						  t_sdl sdl, t_anim anim_sprite);

/*
**	render utils
*/

void		sdl_put_pixel(t_point point, t_sdl sdl);
void		bresen_line(t_sdl sdl, t_point start, t_point end, int color);
int			get_int_from_rgb(int r, int g, int b, int a);
void		get_rgb_from_int(unsigned char *r, unsigned char *g,
							 unsigned char *b, int color);
int			cell_is_empty(t_map map, t_point pos);
int 		get_view_direction(t_ray ray);

/*
**	terminal render
*/

void		draw_terminal(t_wolf *wolf);

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
**	player's actions
*/

void		break_block(t_wolf *wolf);
void		place_block(t_wolf *wolf);
void		change_angle(double *angle, double value);

/*
**	terminal
*/

void			get_term_input(t_wolf *wolf, SDL_Keysym key);
int				check_term(t_wolf *wolf, SDL_Keysym key);
void parse_command(t_wolf *wolf, t_erm *term);

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
