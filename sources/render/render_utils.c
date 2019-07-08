/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:27:06 by rearming          #+#    #+#             */
/*   Updated: 2019/07/08 13:39:36 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sdl_put_pixel(t_wolf *wolf, t_point point)
{
	int 	r;
	int 	g;
	int 	b;
	int 	a;

	r = (point.color >> 16) & 0xFF;
	g = (point.color >> 8) & 0xFF;
	b = point.color & 0xFF;
	a = 255;
	SDL_SetRenderDrawColor(wolf->sdl.rend, r, g, b, a);
	SDL_RenderDrawPoint(wolf->sdl.rend, point.x, point.y);
}

void		parse_color(int *r, int *g, int *b, int color)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int 		get_wall_color(int x, int y, char **map)
{
	if (map[y][x] == '1')
		return (LIGHT_GREEN);
	if (map[y][x] == '2')
		return (LIGHT_BLUE);
	if (map[y][x] == '3')
		return (V_RED);
	if (map[y][x] == '4')
		return (WHITE);
	return (BLACK);
}
