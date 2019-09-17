/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:43:10 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/17 18:54:39 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# include "SDL.h"
# include "SDL2/SDL_ttf.h"

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

char		**parse_params(char **argv, int argc);

/*
**	map parsing
*/

t_map		get_map(char *filename);
char		**fast_gnl(int fd);
int			count_items(t_map *map);
t_point		*find_items(t_map *map);

/*
**	parsing utils
*/

void		check_player_spot(t_map *map, t_point spot);
void		check_cell(t_map *map, int x, int y);
void		check_valid(t_map *map);
int			get_map_height(const char **char_map);
void		convert_spaces(char **map);

/*
**	image parsing
*/

void		get_bmp_image(t_img *bmp, const char *filename);
void		get_tilemap_data(t_img *img, const char *filename);

/*
**	textures parsing
*/

t_textures	get_all_textures(const char **files);
t_sprite	get_sprite(t_img img, int sprite_size, t_point sprite_pos);
int			get_color_from_tilemap(t_img img, int j, int i);
int			get_animation(const char **files, int start,
								t_anim *weapon, int size);
int			**get_texture_table(const char *config);

/*
**	sprites parsing
*/
int			get_all_weapons(const char **files, t_anim *weapons);
t_sprite	*get_minecraft_art(const char *filename);
int			get_player_head(const char **files, t_anim *head, int last_file);

/*
**	render
*/

void		render(t_wolf *wolf);
void		game_window(t_wolf *wolf);
void		render_columns(t_wolf *wolf);
t_ray		raycast(t_wolf *wolf, double angle);
void		draw_column(t_ray *ray, t_wolf *wolf, int win_x);
void		scaled_draw(t_sdl sdl, t_sprite sprite,
					double scale, t_point print_coord);
void		scaled_draw_new(t_wolf *wolf, t_sprite sprite,
					double scale, t_point print_coord);
void		draw_animated(double *frame, int tickrate,
					t_sdl sdl, t_anim anim_sprite);

/*
**	texture render
*/

t_sprite	get_column_sprite(t_ray *ray, t_map *map, t_textures *textures);
int			get_sprite_x_index(t_ray *ray, int texture_size);

/*
**	item render
*/

void		draw_item(t_wolf *wolf, int i, int flag);
void		draw_items(t_wolf *wolf, int *far, int *close);
void		check_walls(t_wolf *wolf);
int			check_walls_utils(t_wolf *wolf, int i);
void		main_menu(t_wolf *wolf);
void		controls(t_wolf *wolf);
void		draw_back_button(t_wolf *wolf);
void		choose_map(t_wolf *wolf, int i);
void		maps_menu(t_wolf *wolf);

/*
**	render utils
*/

void		sdl_put_pixel(t_point *point, t_sdl *sdl);
void		bresen_line(t_sdl sdl, t_point start, t_point end, int color);
int			get_int_from_rgb(int r, int g, int b, int a);
void		get_rgb_from_int(unsigned char *r, unsigned char *g,
							unsigned char *b, int color);
int			cell_is_empty(t_map *map, t_point pos);
int			get_view_direction(t_ray ray);
void		draw_floor_and_sky(t_sdl *sdl, int floor_color);

/*
**	terminal render
*/

void		draw_terminal(t_wolf *wolf);

/*
**	game logic utils
*/

int			is_border_block(t_map *map, t_point block);

/*
**	minimap
*/

void		draw_minimap(t_wolf *wolf);
void		draw_minimap_fov(t_wolf *wolf);

/*
**	minimap utils
*/

int			is_outside_map(t_ray ray, t_wolf *wolf);
t_point		set_head_position(t_wolf *wolf);
t_point		*scale_fov_drawing(t_ray ray, t_wolf *wolf);
void		raycast_draw(t_wolf *wolf, t_dpoint delta);

/*
**	SDL utils
*/

void		sdl_loop(t_wolf *wolf);
void		sdl_clean(t_wolf *wolf);

/*
**	hooks
*/

void		keydown_hook(t_wolf *wolf, SDL_Event *event);
void		keyup_hook(t_wolf *wolf, SDL_Event *event);
void		mouse_motion_hook(t_wolf *wolf, SDL_Event *event);
void		mouse_down_hook(t_wolf *wolf, SDL_Event *event);
void		mouse_wheel_event(t_wolf *wolf, SDL_Event *event);
void		mouse_up_hook(t_wolf *wolf, SDL_Event *event);
void		mouse_actions(t_wolf *wolf);
void		mouse_cords(t_wolf *wolf);

/*
**	player's moves
*/

void		move_forward(t_wolf *wolf);
void		move_back(t_wolf *wolf);
void		move_right(t_wolf *wolf);
void		move_left(t_wolf *wolf);
void		player_run(t_wolf *wolf);
void		player_look(t_wolf *wolf);

/*
**	player's actions
*/

void		break_block(t_wolf *wolf);
void		place_block(t_wolf *wolf);

/*
**	terminal
*/

void		get_term_input(t_wolf *wolf, SDL_Keysym key);
int			check_term(t_wolf *wolf, SDL_Keysym key);
void		parse_command(t_wolf *wolf, t_erm *term);
void		process_full_command(t_wolf *wolf, t_erm *term);

/*
**	terminal actions
*/

void		change_block_index(t_wolf *wolf, t_erm *term);
void		change_all_blocks(t_wolf *wolf, t_erm *term);
void		teleport_player(t_wolf *wolf, t_erm *term);
void		change_channels(t_wolf *wolf, t_erm *term);
void		change_player_fov(t_wolf *wolf, t_erm *term);

/*
**	utils
*/

void		raise_error(int err_code);
void		sdl_exit(t_wolf *wolf);
int			ft_bin_search(int *arr, int elem, int len);

/*
**	debug
*/

#endif
