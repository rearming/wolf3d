/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:28:03 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 14:44:08 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sprite	fix_dir_bug(t_ray *ray, t_textures *textures, t_map *map)
{
	if (ray->direction == VIEW_RIGHT)
	{
		if (map->int_map[(int)(ray->y)][(int)(ray->x - 0.1)])
		{
			if (sin(ray->angle) < 0)
				return (textures->sprites[textures->texture_type][NORTH]);
			else
				return (textures->sprites[textures->texture_type][SOUTH]);
		}
		return (textures->sprites[textures->texture_type][EAST]);
	}
	if (map->int_map[(int)(ray->y)][(int)(ray->x + 0.1)])
	{
		if (sin(ray->angle) < 0)
			return (textures->sprites[textures->texture_type][NORTH]);
		else
			return (textures->sprites[textures->texture_type][SOUTH]);
	}
	return (textures->sprites[textures->texture_type][WEST]);
}

t_sprite	get_sprite_by_side(t_ray *ray, t_textures *textures, t_map *map)
{
	if (ray->direction == VIEW_RIGHT || ray->direction == VIEW_LEFT)
		return (fix_dir_bug(ray, textures, map));
	if (ray->direction == VIEW_UP)
		return (textures->sprites[textures->texture_type][NORTH]);
	if (ray->direction == VIEW_DOWN)
		return (textures->sprites[textures->texture_type][SOUTH]);
	return (textures->sprites[textures->texture_type][WEST]);
}

t_sprite	get_column_sprite(t_ray *ray, t_map *map, t_textures *textures)
{
	int		texture_id;

	texture_id = 1;
	if (textures->render_mode == COMPASS_MODE)
		return (get_sprite_by_side(ray, textures, map));
	if ((int)ray->y < map->height && (int)ray->x < map->width)
		texture_id = map->int_map[(int)ray->y][(int)ray->x];
	if ((textures->texture_type == WOLF3D && texture_id >= WOLF_SPRITES)
	|| ft_bin_search(textures->table[WOLF3D], texture_id, WOLF_SPRITES)
	!= SEARCH_FAIL)
		texture_id = 1;
	if ((textures->texture_type == MINECRAFT && texture_id >= MINE_SPRITES)
	|| ft_bin_search(textures->table[MINECRAFT], texture_id, MINE_SPRITES)
	!= SEARCH_FAIL)
		texture_id = 1;
	texture_id = texture_id > 0 ? texture_id : 1;
	return (textures->sprites[textures->texture_type][texture_id]);
}

int			get_sprite_x_index(t_ray *ray, int texture_size)
{
	if (ray->direction == VIEW_RIGHT)
		return ((int)((double)texture_size * ((ray->y - (int)ray->y))));
	else if (ray->direction == VIEW_LEFT)
		return ((int)((double)texture_size * ((1 - (ray->y - (int)ray->y)))));
	else if (ray->direction == VIEW_DOWN)
		return ((int)((double)texture_size * ((1 - (ray->x - (int)ray->x)))));
	return ((int)((double)texture_size * ((ray->x - (int)ray->x))));
}

int			get_view_direction(t_ray ray)
{
	if (((ray.x - (int)ray.x) > 0.99 || (ray.x - (int)ray.x) < 0.01))
	{
		if (cos(ray.angle) > 0)
			return (VIEW_RIGHT);
		else
			return (VIEW_LEFT);
	}
	else
	{
		if (sin(ray.angle) < 0)
			return (VIEW_UP);
		else
			return (VIEW_DOWN);
	}
}
