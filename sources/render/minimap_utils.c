/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:32:33 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/07 18:49:02 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			is_outside_map(t_ray ray, t_wolf *wolf)
{
	return (!(((wolf->minimap.scale.x / 2) + (ray.x * wolf->minimap.fov_scale
			- wolf->player.x * wolf->minimap.fov_scale) < wolf->minimap.scale.x)
			&& (((wolf->minimap.scale.y / 2) + (ray.y * wolf->minimap.fov_scale
			- wolf->player.y * wolf->minimap.fov_scale)
			< wolf->minimap.scale.y))));
}

t_point		set_head_position(t_wolf *wolf)
{
	return ((t_point){wolf->minimap.scale.x / 2 -
			wolf->textures.head.sprite->size * (wolf->textures.head.scale / 2),
			wolf->minimap.scale.y / 2 - wolf->textures.head.sprite->size
			* (wolf->textures.head.scale / 2), 0, 0});
}

void		raycast_draw(t_wolf *wolf, t_dpoint delta)
{
	t_ray	ray;

	ray.distance = 0;
	while (ray.distance < wolf->minimap.size.x)
	{
		ray.x = wolf->player.x + ray.distance * delta.x;
		ray.y = wolf->player.y + ray.distance * delta.y;
		ray.distance += 0.1;
		if (!is_outside_map(ray, wolf))
			sdl_put_pixel(&(t_point){(wolf->minimap.scale.x / 2) +
			(ray.x * wolf->minimap.fov_scale -
			wolf->player.x * wolf->minimap.fov_scale),
			(wolf->minimap.scale.y / 2) +
			(ray.y * wolf->minimap.fov_scale
			- wolf->player.y * wolf->minimap.fov_scale), 0, M_TURQOISE},
					&wolf->sdl);
		if (wolf->map.int_map[(int)ray.y][(int)ray.x] > 0)
			break ;
	}
}
