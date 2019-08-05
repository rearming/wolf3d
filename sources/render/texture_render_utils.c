/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:28:21 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 12:31:34 by sleonard         ###   ########.fr       */
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
