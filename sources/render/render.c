/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/16 16:06:22 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray		raycast(t_wolf *wolf, double angle)
{
	t_ray	ray;
	double	delta_x;
	double	delta_y;

	delta_x = cos(angle);
	delta_y = sin(angle);
	ray.angle = angle;
	ray.x = wolf->player.x;
	ray.y = wolf->player.y;
	ray.distance = 0;
	while (21)
	{
		if (!cell_is_empty(wolf->map.map[(int)ray.y][(int)ray.x]))
			break ;
		ray.x = wolf->player.x + ray.distance * delta_x;
		ray.y = wolf->player.y + ray.distance * delta_y;
		ray.distance += 0.005;
	}
	ray.direction = get_view_direction(ray);
	return (ray);
}

void		render_columns(t_wolf *wolf)
{
	int		win_x;
	t_ray	ray;

	win_x = 0;
	ray.angle = wolf->player.angle - wolf->player.fov / 2;
	while (win_x < WIN_WIDTH)
	{
		ray = raycast(wolf, ray.angle);
		draw_column(ray, wolf, win_x);
		ray.angle += wolf->player.fov / WIN_WIDTH;
		win_x++;
	}
}

void		draw_floor_and_sky(t_sdl sdl, int floor_color)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			sdl_put_pixel((t_point) {x, y, 0, BLACK}, sdl);
			x++;
		}
		y++;
	}
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			sdl_put_pixel((t_point) {x, y, 0, floor_color}, sdl);
			x++;
		}
		y++;
	}
}

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
				sdl_put_pixel((t_point){x + print_coord.x, y + print_coord.y, 0,
							sprite.data
							[(int)(y / scale)][(int)(x / scale)]}, sdl);
			x++;
		}
		y++;
	}
}

void		draw_weapon(t_wolf *wolf)
{
	if (wolf->textures.frame)
	{
		wolf->textures.frame += (double)wolf->tickrate
				/ wolf->textures.weapons[wolf->player.weapon_type].frequency;
		if (wolf->textures.frame >=
			wolf->textures.weapons[wolf->player.weapon_type].frames)
			wolf->textures.frame = FALSE;
	}
	scaled_draw(wolf->sdl, wolf->textures.
	weapons[wolf->player.weapon_type].sprite[(int)wolf->textures.frame],
				wolf->textures.weapons[wolf->player.weapon_type].scale,
				wolf->textures.weapons[wolf->player.weapon_type].placement);
}

void		render(t_wolf *wolf)
{
	draw_floor_and_sky(wolf->sdl, FLOOR_GREY);
	render_columns(wolf);
	draw_minimap(wolf);
	draw_minimap_fov(wolf);
	draw_weapon(wolf);
	SDL_UpdateTexture(wolf->sdl.texture, NULL, wolf->sdl.pixels,
			WIN_WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}
