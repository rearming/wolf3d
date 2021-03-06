/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/27 22:20:07 by sleonard         ###   ########.fr       */
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
	ray.item_dist = 0;
	while ((int)ray.y < wolf->map.height && (int)ray.x < wolf->map.width)
	{
		if (wolf->map.int_map[(int)ray.y][(int)ray.x] < 0)
			ray.item_dist = ray.distance;
		if (wolf->map.int_map[(int)ray.y][(int)ray.x] > 0)
			break ;
		ray.x = wolf->player.x + ray.distance * delta_x;
		ray.y = wolf->player.y + ray.distance * delta_y;
		ray.distance += 0.01;
	}
	ray.direction = get_view_direction(ray);
	return (ray);
}

void		switch_pxls(int *pix, t_wolf *wolf)
{
	unsigned char	color[3];

	get_rgb_from_int(&color[0], &color[1], &color[2], *pix);
	*pix = get_int_from_rgb(color[wolf->textures.channels[0]],
			color[wolf->textures.channels[1]],
			color[wolf->textures.channels[2]], 0);
}

#pragma clang optimize off

void		draw_column(t_ray *ray, t_wolf *wolf, int win_x)
{
	int			column_y;
	int			win_y;
	int			height;
	t_point		sprite_index;
	t_sprite	sprite;

	win_y = 0;
	ray->distance *= cos(ray->angle - wolf->player.angle);
	height = (int)((double)WIN_HEIGHT / ray->distance);
	column_y = (WIN_HEIGHT - height) / 2;
	sprite = get_column_sprite(ray, &wolf->map, &wolf->textures);
	sprite_index.x = get_sprite_x_index(ray, sprite.size);
	while (win_y < height)
	{
		if (win_x + column_y * WIN_WIDTH > 0
			&& win_x + column_y * WIN_WIDTH < WIN_HEIGHT * WIN_WIDTH
			&& win_y * sprite.height / height < sprite.size)
		{
			wolf->sdl.pixels[win_x + column_y * WIN_WIDTH] =
				sprite.data[win_y * sprite.height / height][sprite_index.x];
			switch_pxls(&wolf->sdl.pixels[win_x + column_y * WIN_WIDTH], wolf);
		}
		column_y++;
		win_y++;
	}
}

#pragma clang optimize on

void		render_columns(t_wolf *wolf)
{
	int		win_x;
	t_ray	ray;

	win_x = 0;
	ray.angle = wolf->player.angle - wolf->player.fov / 2;
	while (win_x < WIN_WIDTH)
	{
		ray = raycast(wolf, ray.angle);
		wolf->map.item_vis[win_x] = ray.item_dist;
		wolf->map.ray_dists[win_x] = ray.distance;
		draw_column(&ray, wolf, win_x);
		ray.angle += wolf->player.fov / WIN_WIDTH;
		win_x++;
	}
}

void		render(t_wolf *wolf)
{
	SDL_LockTexture(wolf->sdl.texture, 0,
			(void**)&wolf->sdl.pixels, &wolf->sdl.pitch);
	mouse_cords(wolf);
	if (wolf->menu_flag == MENU_MAIN)
		main_menu(wolf);
	else if (wolf->menu_flag == MENU_CONTROLS)
		controls(wolf);
	else if (wolf->menu_flag == MENU_MAPS)
		maps_menu(wolf);
	else
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		draw_floor_and_sky(&wolf->sdl, FLOOR_GREY);
		check_walls(wolf);
		game_window(wolf);
	}
	if (wolf->term.opened)
		draw_terminal(wolf);
	SDL_UnlockTexture(wolf->sdl.texture);
	SDL_SetRenderTarget(wolf->sdl.rend, wolf->sdl.texture);
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}
