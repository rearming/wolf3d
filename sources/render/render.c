/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 15:27:08 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double 		ft_dabs(double nbr)
{
	return (nbr > 0 ? nbr : -nbr);
}

t_ray		raycast(t_wolf *wolf, double angle, int *color)
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
	*color = get_wall_color((int)ray.x, (int)ray.y, wolf->map);
	/*if (ft_dabs(ray.x - round(ray.x)) < 0.02 && ft_dabs(ray.y - round(ray.y)) < 0.02)
		*color = BLACK;*/
	//printf("final x: [%f] | ray.y: [%f]\n", x, y);
	return (ray);
}

void		draw_column(t_wolf *wolf, int x, int height, int color)
{
	int		y;
	int 	i;

	y = (WIN_HEIGHT - height) / 2;
	i = 0;
	//printf("height of the column: [%i]\n", height);
	while (i < height)
	{
		sdl_put_pixel((t_point) {x, y, 0, color}, wolf->sdl);
		y++;
		i++;
	}
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
	if (ft_dabs(ray.x - (int)ray.x) > ft_dabs(ray.y - (int)ray.y))
		sprite_index.x = (int)((double)sprite.size * (ft_dabs(ray.x - (int)ray.x)));
	else
		sprite_index.x = (int)((double)sprite.size * (ft_dabs(ray.y - (int)ray.y)));
	i = 0;
	//printf("\nsprite's x: [%i]\n\n", sprite_index.x);
	while (i < height)
	{
		sdl_put_pixel((t_point) {x, y, 0, sprite.data[i * sprite.height / height][sprite_index.x]}, sdl);
		//printf("sprite's y: [%i]\n", sprite_index.y);
		y++;
		i++;
	}
}

void		render_columns(t_wolf *wolf)
{
	int 	i;
	int 	height;
	double 	angle;
	int 	color;
	t_ray	ray;

	i = 0;
	angle = wolf->player.angle - wolf->player.fov / 2;
	while (i < WIN_WIDTH)
	{
		ray = raycast(wolf, angle, &color);
		height = (int)((double)WIN_HEIGHT / ray.distance);
		if (color != HITLER && color != SVA_EAGLE)
			draw_column(wolf, i, height, color);
		else
		{
			if (color == SVA_EAGLE)
				draw_sprite_column(wolf->sdl, wolf->textures.eagle_svaston, ray, i);
			else
				draw_sprite_column(wolf->sdl, wolf->textures.hitler, ray, i);
		}
		angle += wolf->player.fov / WIN_WIDTH;
		i++;
	}
}

void		resize_sprite(int **sprite, double coeff_x, double coeff_y, int sprite_size, t_sdl sdl)
{
	int 	x;
	int 	y;

	y = 0;
	while (y < coeff_y * sprite_size)
	{
		x = 0;
		while (x < coeff_x * sprite_size)
		{
			sdl_put_pixel((t_point){x, y, 0, sprite[(int)(y / coeff_y)][(int)(x / coeff_x)]}, sdl);
			x++;
		}
		y++;
	}
}

void		render(t_wolf *wolf)
{

	SDL_SetRenderTarget(wolf->sdl.rend, wolf->sdl.texture);
	SDL_SetRenderDrawColor(wolf->sdl.rend, 0, 0, 0, 0);
	SDL_RenderClear(wolf->sdl.rend);

	render_columns(wolf);
	draw_minimap(wolf);

	//resize_sprite(wolf->textures.eagle_svaston.data, 0.5, 0.5, wolf->textures.eagle_svaston.size, wolf->sdl);
	/*print_texture(wolf->sdl, 64, 64, wolf->textures.sva_flag, (t_point){0,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.rock_wall, (t_point){64,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.hitler, (t_point){128,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.red_bricks, (t_point){192,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.eagle_svaston, (t_point){256,0});*/

	SDL_SetRenderTarget(wolf->sdl.rend, NULL);
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}