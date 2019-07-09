/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 13:41:18 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double 		ft_dabs(double nbr)
{
	return (nbr > 0 ? nbr : -nbr);
}

double 		raycast(t_wolf *wolf, double angle, int *color)
{
	double 		x;
	double 		y;
	double 		distance;

	x = wolf->player.x;
	y = wolf->player.y;
	distance = 0;
	while (distance < 50)
	{
		if (!cell_is_empty(wolf->map[(int)y][(int)x]))
			break ;
		x = wolf->player.x + distance * cos(angle);
		y = wolf->player.y + distance * sin(angle);
		distance += 0.005;
	}
	*color = get_wall_color((int)x, (int)y, wolf->map);
	if (ft_dabs(x - round(x)) < 0.01 && ft_dabs(y - round(y)) < 0.01)
		*color = BLACK;
	//printf("final x: [%f] | y: [%f]\n", x, y);
	return (distance);
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

void		render_columns(t_wolf *wolf)
{
	int 	i;
	int 	height;
	double 	angle;
	int 	color;

	i = 0;
	angle = wolf->player.angle - wolf->player.fov / 2;
	while (i < WIN_WIDTH)
	{
		height = (int)((double)WIN_HEIGHT / raycast(wolf, angle, &color));
		angle += wolf->player.fov / WIN_WIDTH;
		draw_column(wolf, i, height, color);
		i++;
	}
}

void		render(t_wolf *wolf)
{

	SDL_SetRenderTarget(wolf->sdl.rend, wolf->sdl.texture);
	SDL_SetRenderDrawColor(wolf->sdl.rend, 0, 0, 0, 0);
	SDL_RenderClear(wolf->sdl.rend);

	render_columns(wolf);
	draw_minimap(wolf);

	print_texture(wolf->sdl, 64, 64, wolf->textures.sva_flag, (t_point){0,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.rock_wall, (t_point){64,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.hitler, (t_point){128,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.red_bricks, (t_point){192,0});
	print_texture(wolf->sdl, 64, 64, wolf->textures.eagle_svaston, (t_point){256,0});

	SDL_SetRenderTarget(wolf->sdl.rend, NULL);
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}