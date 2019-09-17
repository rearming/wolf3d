/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:54:14 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/17 18:14:23 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	struct			s_dpoint
{
	double				x;
	double				y;
}						t_dpoint;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct			s_img
{
	int					width;
	int					height;
	int					bpp;
	long				file_size;
	long				img_size;
	int					offset;
	unsigned char		*data;
}						t_img;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	int					*pixels;
	int					pitch;
}						t_sdl;

typedef	struct			s_ttf
{
	TTF_Font			*font;
}						t_ttf;

typedef	struct			s_ray
{
	double				x;
	double				y;
	double				distance;
	double				item_dist;
	double				angle;
	int					direction;
}						t_ray;

typedef struct			s_actions
{
	char				up;
	char				down;
	char				right;
	char				left;
	char				arr_left;
	char				arr_right;
	char				lshift;
	char				lshift_was_pressed;
	char				space;
	char				mouse_left;
	char				mouse_right;
}						t_actions;

typedef struct			s_minimap
{
	double				fov_scale;
	t_point				scale;
	t_point				size;
}						t_minimap;

typedef	struct			s_sprite
{
	int					**data;
	int					size;
	int					width;
	int					height;
	int					bpp;
}						t_sprite;

typedef struct			s_anim
{
	int					type;
	t_sprite			*sprite;
	t_point				placement;
	int					frames;
	double				frequency;
	double				scale;
}						t_anim;

/*
** 114 tiles in wolf tilemap
** 256 tiles in minecraft tilemap
*/

typedef	struct			s_textures
{
	t_sprite			**sprites;
	int					**table;
	int					texture_type;
	int					render_mode;
	t_anim				weapons[WEAPONS_NUM];
	t_anim				head;
	double				weapon_frame;
	double				head_frame;
	int					channels[3];
}						t_textures;

typedef struct			s_map
{
	char				***raw_map;
	char				**char_map;
	int					**int_map;
	int					**backup;
	int					board;
	int					height;
	int					width;
	t_point				player_spawn;
	t_point				*items;
	double				*item_vis;
	double				*ray_dists;
	int					items_nbr;
}						t_map;

typedef struct			s_player
{
	double				x;
	double				y;
	double				fov;
	double				angle;
	double				speed_fwd;
	double				speed_side;
	double				speed_coeff;
	double				ang_speed;
	double				fat;
	int					look_height;
	int					look_coeff;
	int					look_frozen;
	int					weapon_type;
}						t_player;

typedef struct			s_erm
{
	t_point				pos;
	double				scale;
	int					text_color;
	int					line_color;
	char				prepare;
	char				opened;
	char				buffs[TERM_MEM_SIZE][TERM_BUFF_SIZE];
	char				**command;
	int					parsed_command[TERM_CMD_LEN];
	int					i;
	int					cmd_i;
	int					mem_i;
}						t_erm;

typedef struct			s_wolf
{
	t_player			player;
	t_actions			actions;
	t_minimap			minimap;
	t_sdl				sdl;
	t_ttf				ttf;
	t_textures			textures;
	int					tickrate;
	int					no_mouse;
	t_map				map;
	t_erm				term;
	int					flag;
	int					flag_two;
	int					mouse_x;
	int					mouse_y;
	double				dist;
}						t_wolf;

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

# define WOLF_BUFF_SIZE 200000

typedef struct			s_fast_gnl
{
	char				*temp_str;
	char				*backup;
	char				**result;
	char				buf[WOLF_BUFF_SIZE + 1];
	int					read_res;
	size_t				sum_len;
}						t_fast_gnl;

#endif
