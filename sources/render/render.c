/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 20:29:26 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray raycast(t_wolf *wolf, double angle)
{
	t_ray	ray;

	ray.angle = angle;
	ray.x = wolf->player.x;
	ray.y = wolf->player.y;
	ray.distance = 0;
	while (ray.distance < 50)
	{
		if (!cell_is_empty(wolf->map[(int)ray.y][(int)ray.x]))
			break ;
		ray.x = wolf->player.x + ray.distance * cos(angle);
		ray.y = wolf->player.y + ray.distance * sin(angle);
		ray.distance += 0.005;
	}
	//ray.distance *= sin(angle);
	return (ray);
}

t_sprite 	get_sprite_by_side(t_textures sprites, t_ray ray)
{
	if (ray.direction == VIEW_RIGHT)
		return (sprites.red_bricks);
	if (ray.direction == VIEW_LEFT)
		return (sprites.hitler);
	if (ray.direction == VIEW_UP)
		return (sprites.sva_flag);
	if (ray.direction == VIEW_DOWN)
		return (sprites.sva_eagle);
	return (sprites.hitler);
}

int 		get_view_direction(t_ray ray)
{
	if (fabs(ray.x - (int)ray.x) > 0.99 || fabs(ray.x - (int)ray.x) < 0.01)
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

t_sprite	get_column_sprite(t_textures sprites, t_ray ray, const char **map, int render_mode)
{
	int 	sprite_type;

	if (render_mode == COMPASS_MODE)
		return (get_sprite_by_side(sprites, ray));
	sprite_type = get_texture_type((int)ray.x, (int)ray.y, map);
	if (sprite_type == SVA_FLAG)
		return (sprites.sva_flag);
	if (sprite_type == ROCK_WALL)
		return (sprites.rock_wall);
	if (sprite_type == HITLER)
		return (sprites.hitler);
	if (sprite_type == RED_BRICKS)
		return (sprites.red_bricks);
	if (sprite_type == SVA_EAGLE)
		return (sprites.sva_eagle);
	return (sprites.rock_wall);
}

double 		correct_fisheye(t_ray ray)
{
	if (ray.direction == VIEW_RIGHT)
		return (cos(ray.angle));
	if (ray.direction == VIEW_LEFT)
		return (-cos(ray.angle));
	/*if (ray.direction == VIEW_UP)
		return (-sin(ray.angle));
	if (ray.direction == VIEW_DOWN)
		return (sin(ray.angle));
	return (-cos(ray.angle));*/
	return (1);
}

void		draw_sprite_column(t_ray ray, t_wolf *wolf, int win_x)
{
	int			column_y;
	int 		win_y;
	int 		height;
	t_point		sprite_index;
	t_sprite	sprite;

	win_y = 0;
	ray.direction = get_view_direction(ray); //todo fix kostil - get correct algorithm to get player's view direction
	//ray.distance *= correct_fisheye(ray); //todo correct fisheye
	height = (int)((double)WIN_HEIGHT / ray.distance);
	column_y = (WIN_HEIGHT - height) / 2;

	if (ray.direction == VIEW_RIGHT || ray.direction == VIEW_LEFT)
		sprite_index.x = (int)((double)wolf->textures.size * (fabs(ray.y - (int) ray.y)));
	else
		sprite_index.x = (int)((double)wolf->textures.size * (fabs(ray.x - (int)ray.x)));
	sprite = get_column_sprite(wolf->textures, ray, (const char**)wolf->map, wolf->render_mode);
	while (win_y < height)
	{
		sdl_put_pixel((t_point) {win_x, column_y, 0, sprite.data[win_y * sprite.height /
													  height][sprite_index.x]},
					  wolf->sdl);
		column_y++;
		win_y++;
	}
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
		//ray.distance *= cos(wolf->player.angle);
		draw_sprite_column(ray, wolf, win_x);
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
	SDL_UpdateTexture(wolf->sdl.texture, NULL, wolf->sdl.pixels, WIN_WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}