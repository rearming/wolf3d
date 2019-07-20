/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:06:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/20 18:54:08 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		is_outside_map(t_ray ray, t_wolf *wolf)
{
	return (!(((wolf->minimap.scale.x / 2) + (ray.x * wolf->minimap.fov_scale
	- wolf->player.x * wolf->minimap.fov_scale) < wolf->minimap.scale.x)
			&& (((wolf->minimap.scale.y / 2) + (ray.y * wolf->minimap.fov_scale
			- wolf->player.y * wolf->minimap.fov_scale)
			< wolf->minimap.scale.y))));
}

static t_point	set_head_position(t_wolf *wolf)
{
	return ((t_point){wolf->minimap.scale.x / 2 -
	wolf->textures.head.sprite->size * (wolf->textures.head.scale / 2),
	wolf->minimap.scale.y / 2 - wolf->textures.head.sprite->size
	* (wolf->textures.head.scale / 2)});
}

static t_point	scale_fov_drawing(t_ray ray, t_wolf *wolf)
{
	return ((t_point){(wolf->minimap.scale.x / 2) +
	(ray.x * wolf->minimap.fov_scale -
	wolf->player.x * wolf->minimap.fov_scale),
				(wolf->minimap.scale.y / 2) +
				(ray.y * wolf->minimap.fov_scale
				- wolf->player.y * wolf->minimap.fov_scale), 0, M_TURQOISE});
}

static void		raycast_draw(t_wolf *wolf, t_dpoint delta)
{
	t_ray	ray;

	ray.distance = 0;
	while (21)
	{
		ray.x = wolf->player.x + ray.distance * delta.x;
		ray.y = wolf->player.y + ray.distance * delta.y;
		ray.distance += 0.05;
		if (!is_outside_map(ray, wolf))
			sdl_put_pixel(scale_fov_drawing(ray, wolf), wolf->sdl);
		if (!cell_is_empty(wolf->map, (t_point){(int)ray.x, (int)ray.y}))
			break ;
	}
}

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
	wolf->textures.frame = wolf->textures.frame == 0 ? 1 : wolf->textures.frame;
	wolf->textures.head.placement = set_head_position(wolf);
	draw_animated(&wolf->textures.frame, wolf->tickrate,
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
				sdl_put_pixel((t_point){iter.x, iter.y, 0, GREY}, wolf->sdl);
			if (!cell_is_empty(wolf->map, (t_point){(int)map.x, (int)map.y}))
				sdl_put_pixel((t_point){iter.x, iter.y, 0, BLACK}, wolf->sdl);
			iter.x++;
			map.x += (double)wolf->minimap.size.x / wolf->minimap.scale.x;
		}
		iter.y++;
		map.y += (double)wolf->minimap.size.y / wolf->minimap.scale.y;
	}
}
