/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:54:14 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 18:49:50 by sleonard         ###   ########.fr       */
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

typedef struct			s_stb
{
	char				*filename;
	unsigned char		*data;
	int 				width;
	int 				height;
	int 				bpp;
	long				size;
}						t_stb;

typedef struct			s_bmp
{
	int 				width;
	int 				height;
	int 				bpp;
	long 				file_size;
	long 				img_size;
	int 				offset;
	int 				color_used;
	int					*table;
	unsigned char 		*data;
}						t_bmp;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	int					*pixels; //todo mb uint32_t?
}						t_sdl;

typedef	struct			s_ray
{
	double 				x;
	double 				y;
	double 				distance;
	double 				angle;
	int 				direction;
}						t_ray;

typedef struct			s_player
{
	double 				x;
	double 				y;
	double 				fov;
	double 				angle;
	double 				speed_fwd;
	double 				speed_side;
	double 				ang_speed;
	double 				fat;
}						t_player;

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
}						t_sprite;

typedef	struct 			s_textures
{
	t_sprite 			sva_flag;
	t_sprite 			rock_wall;
	t_sprite 			hitler;
	t_sprite 			red_bricks;
	t_sprite 			sva_eagle;
	int 				size;
}						t_textures;

typedef struct			s_wolf
{
	t_player			player;
	t_minimap			minimap;
	t_sdl				sdl;
	t_textures			textures;
	int 				render_mode;
	char				**map;
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


# define CL_BUFF_SIZE 10000

typedef struct			s_gnl_fdf
{
	char				*temp_str;
	char				*backup;
	char 				**result;
	char				buf[CL_BUFF_SIZE + 1];
	int					read_res;
	size_t				sum_len;

}						t_gnl_fdf;

#endif
