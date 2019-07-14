/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/14 18:34:32 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray		raycast(t_wolf *wolf, double angle)
{
	t_ray	ray;
	double	deltaX;
	double	deltaY;

	deltaX = cos(angle);
	deltaY = sin(angle);
	ray.angle = angle;
	ray.x = wolf->player.x;
	ray.y = wolf->player.y;
	ray.distance = 0;
	while (21)
	{
		if (!cell_is_empty(wolf->map.map[(int)ray.y][(int)ray.x]))
			break ;
		ray.x = wolf->player.x + ray.distance * deltaX;
		ray.y = wolf->player.y + ray.distance * deltaY;
		ray.distance += 0.005;
	}
	return (ray);
}

void		render_columns(t_wolf *wolf)
{
	int 	win_x;
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
	int 	x;
	int 	y;

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

void		render(t_wolf *wolf)
{
	draw_floor_and_sky(wolf->sdl, FLOOR_GREY);
	render_columns(wolf);
	draw_minimap(wolf);
	draw_minimap_fov(wolf);
	SDL_UpdateTexture(wolf->sdl.texture, NULL, wolf->sdl.pixels,
			WIN_WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}
