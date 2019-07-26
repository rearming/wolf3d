/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:28:21 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 15:47:13 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sprite	fix_dir_bug(t_ray *ray, t_textures textures, t_map map)
{
	if (ray->direction == VIEW_RIGHT)
	{
		if (map.int_map[(int)(ray->y)][(int)(ray->x - 0.1)])
		{
			if (sin(ray->angle) < 0)
				return (textures.sprites[textures.texture_mode][SVA_FLAG]);
			else
				return (textures.sprites[textures.texture_mode][WOOD]);
		}
		return (textures.sprites[textures.texture_mode][RED_BRICKS]);
	}
	if (map.int_map[(int)(ray->y)][(int)(ray->x + 0.1)])
	{
		if (sin(ray->angle) < 0)
			return (textures.sprites[textures.texture_mode][SVA_FLAG]);
		else
			return (textures.sprites[textures.texture_mode][WOOD]);
	}
	return (textures.sprites[textures.texture_mode][HITLER]);
}

t_sprite	get_sprite_by_side(t_ray *ray, t_textures textures, t_map map)
{
	if (ray->direction == VIEW_RIGHT || ray->direction == VIEW_LEFT)
		return (fix_dir_bug(ray, textures, map));
	if (ray->direction == VIEW_UP)
		return (textures.sprites[textures.texture_mode][SVA_FLAG]);
	if (ray->direction == VIEW_DOWN)
		return (textures.sprites[textures.texture_mode][WOOD]);
	return (textures.sprites[textures.texture_mode][HITLER]);
}

//todo сделать чек некрасивых текстур (можно тоже по таблице) / из конфиг файла

t_sprite	get_column_sprite(t_ray *ray, t_map map, t_textures textures)
{
	int 	texture_id;

	if (textures.render_mode == COMPASS_MODE)
		return (get_sprite_by_side(ray, textures, map));
	texture_id = map.int_map[(int)ray->y][(int)ray->x];
	if (textures.render_mode == WOLF3D && texture_id >= WOLF_SPRITES)
		texture_id = 1;
	if (textures.render_mode == MINECRAFT && texture_id >= MINE_SPRITES)
		texture_id = 1;
	return (textures.sprites[textures.texture_mode][texture_id]);
}

int			get_sprite_x_index(t_ray ray, int texture_size)
{
	if (ray.direction == VIEW_RIGHT || ray.direction == VIEW_LEFT)
		return((int)((double)texture_size * (fabs(ray.y - (int)ray.y))));
	return ((int)((double)texture_size * (fabs(ray.x - (int)ray.x))));
}

int 		get_view_direction(t_ray ray)
{
	if ((fabs(ray.x - (int)ray.x) > 0.99 || fabs(ray.x - (int)ray.x) < 0.01))
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

void		draw_column(t_ray *ray, t_wolf *wolf, int win_x)
{
	int			column_y;
	int 		win_y;
	int 		height;
	t_point		sprite_index;
	t_sprite	sprite;

	win_y = 0;
	ray->distance *= cos(ray->angle - wolf->player.angle);
	height = (int)((double)WIN_HEIGHT / ray->distance);
	if (height > WIN_HEIGHT * 2)
		height = WIN_HEIGHT * 2;
	column_y = (WIN_HEIGHT - height) / 2;
	sprite = get_column_sprite(ray, wolf->map, wolf->textures);
	sprite_index.x = get_sprite_x_index(*ray, sprite.size);
	while (win_y < height)
	{
		if (win_x + column_y * WIN_WIDTH > 0)
			wolf->sdl.pixels[win_x + column_y * WIN_WIDTH] =
					sprite.data[win_y * sprite.height / height][sprite_index.x];
		column_y++;
		win_y++;
	}
}
