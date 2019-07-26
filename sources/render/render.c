/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 12:07:12 by sleonard         ###   ########.fr       */
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
	while ((int)ray.y < wolf->map.height && (int)ray.x < wolf->map.width)
	{
		if (wolf->map.int_map[(int)ray.y][(int)ray.x] != 0)
			break ;
		ray.x = wolf->player.x + ray.distance * delta_x;
		ray.y = wolf->player.y + ray.distance * delta_y;
		ray.distance += 0.01;
	}
	ray.direction = get_view_direction(&ray);
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
		draw_column(&ray, wolf, win_x);
		ray.angle += wolf->player.fov / WIN_WIDTH;
		win_x++;
	}
}

void		draw_floor_and_sky(t_sdl sdl, int floor_color) //todo make floor and celling
{
	long	y;
	long	half_screen;

	y = 0;
	half_screen = WIN_HEIGHT / 2 * WIN_WIDTH;
	while (y < half_screen)
	{
		sdl.pixels[y] = BLACK;
		y++;
	}
	y = half_screen;
	half_screen *= 2;
	while (y < half_screen)
	{
		sdl.pixels[y] = floor_color;
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

void		draw_animated(double *frame, int tickrate,
						  t_sdl sdl, t_anim anim_sprite)
{
	if (*frame)
	{
		*frame += (double)tickrate / anim_sprite.frequency;
		if (*frame >= anim_sprite.frames)
			*frame = FALSE;
	}
	scaled_draw(sdl, anim_sprite.sprite[(int)*frame], anim_sprite.scale,
			anim_sprite.placement);
}


void 		draw_item(t_wolf *wolf)
{
	t_point		item;
	t_point		res;
	double 		atan_item;
	double 		player;

	item = wolf->map.items[0];

	res.x = item.x - (int)wolf->player.x;
	res.y = item.y - (int)wolf->player.y;
	atan_item = atan2(res.y, res.x);
	//player = atan2(wolf->player.x, wolf->player.y);
	if (atan_item <= wolf->player.angle + wolf->player.fov / 2 && atan_item >= wolf->player.angle - wolf->player.fov / 2)
	{
		printf("%f\n", atan_item);
		printf("visiable!\n");
		printf("max: [%f] | min: [%f]\n", wolf->player.angle + wolf->player.fov / 2, wolf->player.angle - wolf->player.fov / 2);
	}
	else
	{
		printf("NOT\n");
		printf("max: [%f] | min: [%f]\n", wolf->player.angle + wolf->player.fov / 2, wolf->player.angle - wolf->player.fov / 2);
		printf("item: [%f]\n", atan_item);
	//	printf("player: [%f]\n", new_angle);
	}
	//printf("item's x: [%i] | y: [%i]\n", item.x, item.y);
}

void		render(t_wolf *wolf)
{
	draw_floor_and_sky(wolf->sdl, FLOOR_GREY);
	render_columns(wolf);
	draw_minimap(wolf);
	draw_minimap_fov(wolf);
	draw_animated(&wolf->textures.w_frame, wolf->tickrate, wolf->sdl,
			wolf->textures.weapons[(int) wolf->player.weapon_type]);
	//draw_item(wolf);
	if (wolf->term.opened)
		draw_terminal(wolf);
	SDL_UpdateTexture(wolf->sdl.texture, NULL, wolf->sdl.pixels,
			WIN_WIDTH * sizeof(int));
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}
