/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:06:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/16 17:37:09 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_minimap_fov(t_wolf *wolf)
{
	t_ray		ray;
	double 		angle;
	int 		fov;
	int 		base_ang;

	angle = wolf->player.angle - wolf->player.fov / 2;
	fov = 180 / M_PI * wolf->player.fov;
	base_ang = fov;
	while (fov)
	{
		ray.distance = 0;
		while (21)
		{
			ray.x = wolf->player.x + ray.distance * cos(angle);
			ray.y = wolf->player.y + ray.distance * sin(angle);
			ray.distance += 0.05;
			sdl_put_pixel((t_point)
				{ray.x * wolf->minimap.scale.x,
	 ray.y * wolf->minimap.scale.y, 0, M_TURQOISE}, wolf->sdl);
			if (!cell_is_empty(wolf->map.map[(int)ray.y][(int)ray.x]))
				break;
		}
		angle += wolf->player.fov / base_ang;
		fov--;
	}
}

void		draw_minimap(t_wolf *wolf)
{
	t_point		map_xy;

	map_xy.y = 0;
	while (map_xy.y < wolf->map.height * wolf->minimap.scale.y)
	{
		map_xy.x = 0;
		while (map_xy.x < wolf->map.width * wolf->minimap.scale.x)
		{
			if (cell_is_empty(wolf->map.map[map_xy.y / wolf->minimap.scale.y]
			[map_xy.x / wolf->minimap.scale.x]))
				sdl_put_pixel((t_point) {map_xy.x, map_xy.y, 0, GREY}, wolf->sdl);
			else
				sdl_put_pixel((t_point)
				{map_xy.x, map_xy.y, 0,
			get_texture_type(map_xy.x / wolf->minimap.scale.x,map_xy.y / wolf->minimap.scale.y,
					(const char **)wolf->map.map)}, wolf->sdl); //todo fix wall colors on minimap
			map_xy.x++;
		}
		map_xy.y++;
	}
}