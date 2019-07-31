/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:27:06 by rearming          #+#    #+#             */
/*   Updated: 2019/07/31 20:00:35 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			cell_is_empty(t_map map, t_point pos)
{
	if (pos.x >= map.width || pos.x < 0 || pos.y >= map.height || pos.y < 0)
		return (1);
	if (map.int_map[pos.y][pos.x] > 0)
			return (0);
	return (1);
}

inline void		sdl_put_pixel(t_point *point, t_sdl *sdl)
{
	if (point->x >= 0 && point->y >= 0
		&& point->x < WIN_WIDTH && point->y < WIN_HEIGHT)
			sdl->pixels[point->x + point->y * WIN_WIDTH] = point->color;
}

int			get_int_from_rgb(int r, int g, int b, int a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void		get_rgb_from_int(unsigned char *r, unsigned char *g,
							 unsigned char *b, int color)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}
