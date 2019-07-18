/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:28:21 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/18 19:51:04 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sprite 	fix_dir_bug(t_wolf *wolf, t_ray *ray)
{
	if (ray->direction == VIEW_RIGHT)
	{
		if (!cell_is_empty(wolf->map.map[(int)(ray->y)][(int)(ray->x - 0.1)]))
		{
			if (sin(ray->angle) < 0)
				return (wolf->textures.sva_flag);
			else
				return (wolf->textures.wood);
		}
		return (wolf->textures.red_bricks);
	}
	if (!cell_is_empty(wolf->map.map[(int)(ray->y)][(int)(ray->x + 0.1)]))
	{
		if (sin(ray->angle) < 0)
			return (wolf->textures.sva_flag);
		else
			return (wolf->textures.wood);
	}
	return (wolf->textures.hitler);
}

t_sprite	get_sprite_by_side(t_ray *ray, t_wolf *wolf)
{
	if (ray->direction == VIEW_RIGHT || ray->direction == VIEW_LEFT)
		return (fix_dir_bug(wolf, ray));
	if (ray->direction == VIEW_UP)
		return (wolf->textures.sva_flag);
	if (ray->direction == VIEW_DOWN)
		return (wolf->textures.wood);
	return (wolf->textures.hitler);
}

t_sprite	get_column_sprite(t_ray *ray, const char **map,
		int render_mode, t_wolf *wolf)
{
	int 	sprite_type;

	if (render_mode == COMPASS_MODE)
		return (get_sprite_by_side(ray, wolf));
	sprite_type = get_texture_type((int)ray->x, (int)ray->y, map);
	if (sprite_type == SVA_FLAG)
		return (wolf->textures.sva_flag);
	if (sprite_type == ROCK_WALL)
		return (wolf->textures.rock_wall);
	if (sprite_type == HITLER)
		return (wolf->textures.hitler);
	if (sprite_type == RED_BRICKS)
		return (wolf->textures.red_bricks);
	if (sprite_type == SVA_EAGLE)
		return (wolf->textures.sva_eagle);
	return (wolf->textures.rock_wall);
}

int			get_sprite_index(t_ray ray, int texture_size, t_wolf *wolf)
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

void		draw_column(t_ray ray, t_wolf *wolf, int win_x)
{
	int			column_y;
	int 		win_y;
	int 		height;
	t_point		sprite_index;
	t_sprite	sprite;

	win_y = 0;
	ray.distance *= cos(ray.angle - wolf->player.angle);
	height = (int)((double)WIN_HEIGHT / ray.distance);
	column_y = (WIN_HEIGHT - height) / 2;
	sprite = get_column_sprite(&ray,
							   (const char **) wolf->map.map, wolf->render_mode,
							   wolf);
	sprite_index.x = get_sprite_index(ray, sprite.size, wolf);
	while (win_y < height)
	{
		sdl_put_pixel((t_point) {win_x, column_y, 0, sprite.data
					  [win_y * sprite.height / height][sprite_index.x]},
					  wolf->sdl);
		column_y++;
		win_y++;
	}
}
