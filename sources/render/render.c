/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 12:35:35 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int 		get_wall_color(int x, int y, char **map)
{
	if (map[y][x] == '1')
		return (LIGHT_GREEN);
	if (map[y][x] == '2')
		return (LIGHT_BLUE);
	if (map[y][x] == '3')
		return (V_RED);
	if (map[y][x] == '4')
		return (WHITE);
	return (BLACK);
}

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
	printf("distance: [%f]\n", distance);
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

	parse_color(&r, &g, &b, color);
	y = (WIN_HEIGHT - height) / 2;
	i = 0;
	//printf("height of the column: [%i]\n", height);
	while (i < height)
	{
		SDL_SetRenderDrawColor(wolf->sdl.rend, r, g, b, 255);
		SDL_RenderDrawPoint(wolf->sdl.rend, x, y);
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
	angle = wolf->player.angle + wolf->player.fov / 5;
	while (i < WIN_WIDTH)
	{
		height = (int)((double)WIN_HEIGHT / raycast(wolf, angle, &color));
		angle -= wolf->player.fov / WIN_WIDTH;
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
	SDL_SetRenderTarget(wolf->sdl.rend, NULL);
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}