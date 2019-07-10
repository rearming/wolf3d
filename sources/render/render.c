/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 14:30:41 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray		raycast(t_wolf *wolf, double angle, int *texture_type)
{
	t_ray	ray;

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
	*texture_type = get_texture_type((int)ray.x, (int)ray.y, wolf->map);
	//printf("final ray.x: [%f] | ray.y: [%f]\n", x, y);
	return (ray);
}

void		draw_sprite_column(t_sdl sdl, t_sprite sprite, t_ray ray, int x)
{
	int		y;
	int 	i;
	int 	height;
	t_point	sprite_index;


	height = (int)((double)WIN_HEIGHT / ray.distance);
	y = (WIN_HEIGHT - height) / 2;
	sprite_index.y = 0;
	sprite_index.x = (int)((double)sprite.size * (fabs(ray.x - (int)ray.x)));
	//printf("sprite_width: [%i]\n", sprite.width);
	if (!sprite_index.x || sprite_index.x == sprite.width - 1)
		sprite_index.x = (int)((double)sprite.size * (fabs(ray.y - (int)ray.y)));
	i = 0;
	//printf("\nsprite's x: [%i]\n\n", sprite_index.x);
	while (i < height)
	{
		sdl_put_pixel((t_point) {x, y, 0, sprite.data[i * sprite.height /
													  height][sprite_index.x]},
					  sdl);
		y++;
		i++;
	}
}

t_sprite	get_map_sprite(int sprite_type, t_textures sprites)
{
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

void		render_columns(t_wolf *wolf)
{
	int 	i;
	double 	angle;
	int 	sprite_type;
	t_ray	ray;

	i = 0;
	angle = wolf->player.angle - wolf->player.fov / 2;
	while (i < WIN_WIDTH)
	{
		ray = raycast(wolf, angle, &sprite_type);
		draw_sprite_column(wolf->sdl, get_map_sprite(sprite_type, wolf->textures), ray, i);
		angle += wolf->player.fov / WIN_WIDTH;
		i++;
	}
}

void		draw_floor(t_sdl sdl, int floor_color)
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
	draw_floor(wolf->sdl, FLOOR_GREY);
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