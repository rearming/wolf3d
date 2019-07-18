/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:54:14 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/16 17:13:49 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct			s_img
{
	int 				width;
	int 				height;
	int 				bpp;
	long 				file_size;
	long 				img_size;
	int 				offset;
	unsigned char 		*data;
}						t_img;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	int					*pixels;
}						t_sdl;

typedef	struct			s_ray
{
	double 				x;
	double 				y;
	double 				distance;
	double 				angle;
	int 				direction;
}						t_ray;

typedef struct			s_actions
{
	char				up;
	char 				down;
	char 				right;
	char 				left;
	char 				lshift;
	char 				lshift_was_pressed;
	char 				mouse_left;
	char 				mouse_right;
}						t_actions;

typedef struct			s_minimap
{
	t_point				scale;
}						t_minimap;

typedef	struct			s_sprite
{
	int					**data;
	int 				size;
	int 				width;
	int 				height;
	int 				bpp;
}						t_sprite;

typedef struct			s_weapon
{
	int 				type;
	t_sprite			*sprite;
	t_point				placement;
	int 				frames;
	int 				frequency;
	double				scale;
}						t_weapon;

typedef	struct 			s_textures
{
	t_sprite 			sva_flag;
	t_sprite 			rock_wall;
	t_sprite 			hitler;
	t_sprite 			red_bricks;
	t_sprite 			sva_eagle;
	t_sprite			wood;
	t_weapon			weapons[WEAPONS_NUM];
	double 				frame;
}						t_textures;

typedef struct			s_map
{
	char 				**map;
	int 				height;
	int 				width;
	t_point				player_spawn;
}						t_map;

typedef struct			s_player
{
	double 				x;
	double 				y;
	double 				fov;
	double 				angle;
	double 				base_speed;
	double 				speed_fwd;
	double 				speed_side;
	double 				ang_speed;
	double 				fat;
	int 				weapon_type;
}						t_player;

typedef struct			s_wolf
{
	t_player			player;
	t_actions			actions;
	t_minimap			minimap;
	t_sdl				sdl;
	t_textures			textures;
	int 				render_mode;
	int 				tickrate;
	int 				no_mouse;
	t_map				map;
}						t_wolf;

typedef struct			s_color
{
	int 				r;
	int 				g;
	int 				b;
	int 				a;
}						t_color;

typedef struct			s_line
{
	t_point				start;
	t_point				end;
	t_point				point;
	t_point				delta;
	int					steep;
	int					error;
	int					ystep;
}						t_line;

typedef struct			s_command
{
	int					status;
	int					action;
	int					frac_type;
	int					jump_area;
}						t_command;

typedef struct			s_erm
{
	char				buff[100];
	char				prev_cmd[10][100];
	int					i;
	int					cmd_i;
	t_command			cmd;
}						t_erm;


# define WOLF_BUFF_SIZE 2000000

typedef struct			s_fast_gnl
{
	char				*temp_str;
	char				*backup;
	char 				**result;
	char				buf[WOLF_BUFF_SIZE + 1];
	int					read_res;
	size_t				sum_len;
}						t_fast_gnl;

#endif
