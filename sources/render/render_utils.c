/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:27:06 by rearming          #+#    #+#             */
/*   Updated: 2019/07/10 08:12:38 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int 		cell_is_empty(char cell)
{
	if (cell != '0' && cell != PLAYER_POS)
		return (0);
	return (1);
}

void		sdl_put_pixel(t_point point, t_sdl sdl)
{
	int 	r;
	int 	g;
	int 	b;
	int 	a;

	r = (point.color >> 16) & 0xFF;
	g = (point.color >> 8) & 0xFF;
	b = point.color & 0xFF;
	a = 255;
	SDL_SetRenderDrawColor(sdl.rend, r, g, b, a);
	SDL_RenderDrawPoint(sdl.rend, point.x, point.y);
}

int 		get_int_from_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void		get_rgb_from_int(int *r, int *g, int *b, int color)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int 		get_texture_type(int x, int y, char **map)
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
