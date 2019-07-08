/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 15:28:53 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double 		raycast(t_wolf *wolf, double angle, int *color)
{
	double 		x;
	double 		y;
	double 		distance;

	x = wolf->player.x;
	y = wolf->player.y;
	distance = 0;
	//printf("angle: [%f]\n", angle / M_PI * 180);
	while (distance < 50)
	{
		//printf("x: [%f] | y: [%f]\n", x, y);
		if (wolf->map[(int)y][(int)x] != '0')
			break ;
		x = wolf->player.x + distance * cos(angle);
		y = wolf->player.y + distance * sin(angle);
		distance += 0.005;
	}
	//printf("distance: [%f]\n", distance);
	//printf("\n");
	*color = get_wall_color((int)x, (int)y, wolf->map);
	return (distance);
}

void		draw_column(t_wolf *wolf, int x, int height, int color)
{
	int		y;
	int 	i;

	int 	r;
	int 	g;
	int 	b;

	y = (WIN_HEIGHT - height) / 2;
	i = 0;
	//printf("height of the column: [%i]\n", height);
	while (i < height)
	{
		sdl_put_pixel(wolf, (t_point){x, y, 0, color});
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

	i = WIN_WIDTH;
	angle = wolf->player.angle + wolf->player.fov / 2;
	while (i)
	{
		height = (int)((double)WIN_HEIGHT / raycast(wolf, angle, &color));
		angle -= wolf->player.fov / WIN_WIDTH;
		draw_column(wolf, i, height, color);
		i--;
	}
}

void		render(t_wolf *wolf)
{
	SDL_SetRenderTarget(wolf->sdl.rend, wolf->sdl.texture);
	SDL_SetRenderDrawColor(wolf->sdl.rend, 0, 0, 0, 0);
	SDL_RenderClear(wolf->sdl.rend);
	render_columns(wolf);
	draw_minimap(wolf);
	SDL_SetRenderTarget(wolf->sdl.rend, NULL);
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}