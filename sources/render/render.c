/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/11 19:04:59 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sdl_put_pixel(t_wolf *wolf, t_point point)
{
	int 	r;
	int 	g;
	int 	b;
	int 	a;

	r = (point.color >> 16) & 0xFF;
	g = (point.color >> 8) & 0xFF;
	b = point.color & 0xFF;
	a = 0;
	SDL_SetRenderDrawColor(wolf->sdl.rend, r, g, b, a);
	SDL_RenderDrawPoint(wolf->sdl.rend, point.x, point.y);
}

void		render(t_wolf *wolf)
{
	SDL_RenderClear(wolf->sdl.rend);

	t_point		start;
	t_point		end;

	start.x = 200;
	start.y = 200;
	end.x = 1000;
	end.y = 200;
	start.color = LIGHT_GREEN;
	bresen_line(wolf, start, end);
	start.x = 0;
	start.y = 0;
	end.x = 1000;
	end.y = 200;
	bresen_line(wolf, start, end);
	SDL_RenderPresent(wolf->sdl.rend);
}