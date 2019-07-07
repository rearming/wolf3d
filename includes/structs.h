/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:54:14 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/07 12:47:48 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
}						t_sdl;

typedef struct			s_stb
{
	char				*filename;
	unsigned char		*data;
	int 				x;
	int 				y;
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

typedef struct			s_player
{
	double 				x;
	double 				y;
	double 				fov;
	double 				angle;
	double 				speed;
}						t_player;

typedef struct			s_wolf
{
	t_player			player;
	char				**map;
	t_sdl				sdl;
	t_bmp				bmp;
	t_stb				stb;
	int 				offset_x;
	int 				offset_y;
}						t_wolf;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

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
	char				buf[CL_BUFF_SIZE + 1];
	int					read_res;
	size_t				sum_len;
}						t_gnl_fdf;

#endif
