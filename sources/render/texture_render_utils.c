/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:28:21 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/27 19:25:39 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		scaled_draw(t_sdl sdl, t_sprite sprite,
						double scale, t_point print_coord)
{
	int		x;
	int		y;

	y = 0;
	scale = scale < 20 ? scale : 20;
	while (y < scale * sprite.height)
	{
		x = 0;
		while (x < scale * sprite.width)
		{
			if ((sprite.data[(int)(y / scale)][(int)(x / scale)] >> 24) != 0)
				sdl_put_pixel(&(t_point){x + print_coord.x, y + print_coord.y,
					0, sprite.data[(int)(y / scale)][(int)(x / scale)]}, &sdl);
			x++;
		}
		y++;
	}
}

void		draw_animated(double *frame, int tickrate,
						t_sdl sdl, t_anim anim_sprite)
{
	if (*frame)
	{
		*frame += (double)tickrate * anim_sprite.frequency;
		if ((int)(*frame) >= anim_sprite.frames)
			*frame = anim_sprite.type == HEAD ? 1 : 0;
	}
	scaled_draw(sdl, anim_sprite.sprite[(int)(*frame)], anim_sprite.scale,
				anim_sprite.placement);
}

void		scaled_draw_new(t_wolf *wolf, t_sprite sprite,
double scale, t_point print_coord)
{
	int		x;
	int		y;
	t_ray	ray;

	scale = scale < 20 ? scale : 20;
	x = 0;
	while (x < scale * sprite.width)
	{
		y = 0;
		ray = raycast(wolf, ((double)(print_coord.x + x) / 22 / 180 * M_PI));
		if (ray.distance > print_coord.z)
		{
			while (y < scale * sprite.height)
			{
				if ((sprite.data[(int)(y / scale)][(int)(x / scale)] >> 24))
					sdl_put_pixel(&(t_point){x + print_coord.x, y
					+ print_coord.y, 0, sprite.data[(int)(y / scale)]
					[(int)(x / scale)]}, &(wolf->sdl));
				y++;
			}
		}
		x++;
	}
}

int			check_walls_utils(t_wolf *wolf, int i)
{
	t_ray	ray;
	double	coord[3];
	double	dist;

	coord[0] = wolf->map.items[i].x + 0.5 - wolf->player.x;
	coord[1] = wolf->map.items[i].y + 0.5 - wolf->player.y;
	coord[2] = atan2(coord[1], coord[0]);
	if (coord[2] < 0)
		coord[2] += M_PI * 2;
	ray = raycast(wolf, coord[2]);
	dist = sqrt(coord[0] * coord[0] + coord[1] * coord[1]);
	if (ray.distance < dist)
		return (1);
	return (0);
}
