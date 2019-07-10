/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 19:02:39 by sleonard         ###   ########.fr       */
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
	//printf("final ray.x: [%f] | ray.y: [%f]\n", x, y);
	return (ray);
}

t_sprite 	get_sprite_by_side(t_textures sprites, t_ray ray)
{
	if (ray.wall_placement == VERTICAL)
	{
		if (cos(ray.angle) > 0)
			return (sprites.red_bricks);
		else
			return (sprites.rock_wall);
	}
	else
	{
		if (sin(ray.angle) < 0)
			return (sprites.sva_flag);
		else
			return (sprites.sva_eagle);
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

int 		get_wall_placement(t_ray ray)
{
	if (fabs(ray.x - (int)ray.x) > 0.99 || fabs(ray.x - (int)ray.x) < 0.01)
		return (VERTICAL);
	return (HORIZONTAL);
}

void		draw_sprite_column(t_ray ray, t_wolf *wolf, int win_x)
{
	int			column_y;
	int 		win_y;
	int 		height;
	t_point		sprite_index;
	t_sprite	sprite;

	win_y = 0;
	height = (int)((double)WIN_HEIGHT / ray.distance);
	column_y = (WIN_HEIGHT - height) / 2;
	ray.wall_placement = get_wall_placement(ray);
	if (ray.wall_placement == VERTICAL)
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

	//resize_sprite(wolf->textures.sva_eagle.data, 0.5, 0.5, wolf->textures.sva_eagle.size, wolf->sdl);
	/*print_texture(wolf->sdl, 64, 64, wolf->textures.sva_flag, (t_point){0,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.rock_wall, (t_point){64,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.hitler, (t_point){128,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.red_bricks, (t_point){192,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.sva_eagle, (t_point){256,0});*/

	SDL_UpdateTexture(wolf->sdl.texture, NULL, wolf->sdl.pixels, WIN_WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}