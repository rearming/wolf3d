/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:27:06 by rearming          #+#    #+#             */
/*   Updated: 2019/07/18 20:29:03 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int 		cell_is_empty(char cell)
{
	if (cell != '0' && cell != PLAYER_POS && cell != ' '
		&& cell != '7' && cell != '8' && cell != '9')
		return (0);
	return (1);
}

void		sdl_put_pixel(t_point point, t_sdl sdl)
{
	if (point.x >= 0 && point.y >= 0
		&& point.x < WIN_WIDTH && point.y < WIN_HEIGHT)
			sdl.pixels[point.x + point.y * WIN_WIDTH] = point.color;
}

int			get_int_from_rgb(int r, int g, int b, int a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void		get_rgb_from_int(int *r, int *g, int *b, int color)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int 		get_texture_type(int x, int y, const char **map)
{
	if (map[y][x] == '1')
		return (ROCK_WALL);
	if (map[y][x] == '2')
		return (SVA_EAGLE);
	if (map[y][x] == '3')
		return (RED_BRICKS);
	if (map[y][x] == '4')
		return (SVA_FLAG);
	if (map[y][x] == '6')
		return (HITLER);
	return (BLACK);
}
