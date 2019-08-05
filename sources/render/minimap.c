/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:06:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 12:26:26 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_minimap_fov(t_wolf *wolf)
{
	double		angle;
	int			fov;
	int			base_ang;

	angle = wolf->player.angle - wolf->player.fov / 2;
	fov = 180 / M_PI * wolf->player.fov;
	base_ang = fov;
	while (fov)
	{
		raycast_draw(wolf, (t_dpoint){cos(angle), sin(angle)});
		angle += wolf->player.fov / base_ang;
		fov--;
	}
	wolf->textures.head_frame =
			wolf->textures.head_frame == 0 ? 1 : wolf->textures.head_frame;
	wolf->textures.head.placement = set_head_position(wolf);
	draw_animated(&wolf->textures.head_frame, wolf->tickrate,
				wolf->sdl, wolf->textures.head);
}

void			draw_minimap(t_wolf *wolf)
{
	t_point		iter;
	t_dpoint	map;

	iter.y = 0;
	map.y = wolf->player.y - (double)wolf->minimap.size.y / 2;
	while (iter.y < wolf->minimap.scale.y)
	{
		iter.x = 0;
		map.x = wolf->player.x - (double)wolf->minimap.size.x / 2;
		while (iter.x < wolf->minimap.scale.x)
		{
			if (cell_is_empty(wolf->map, (t_point){(int)map.x, (int)map.y}))
				sdl_put_pixel(&(t_point){iter.x, iter.y, 0, GREY}, &wolf->sdl);
			if (cell_is_empty(wolf->map, (t_point){(int)map.x, (int)map.y})
			== ITEM)
				sdl_put_pixel(&(t_point){iter.x, iter.y, 0, RED}, &wolf->sdl);
			if (!cell_is_empty(wolf->map, (t_point){(int)map.x, (int)map.y}))
				sdl_put_pixel(&(t_point){iter.x, iter.y, 0, BLACK}, &wolf->sdl);
			iter.x++;
			map.x += (double)wolf->minimap.size.x / wolf->minimap.scale.x;
		}
		iter.y++;
		map.y += (double)wolf->minimap.size.y / wolf->minimap.scale.y;
	}
}
