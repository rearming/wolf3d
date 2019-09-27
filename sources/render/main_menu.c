/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:09:32 by bbear             #+#    #+#             */
/*   Updated: 2019/09/27 18:43:22 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*text_for_button(t_wolf *wolf, int i, SDL_Color col)
{
	if (i == 1 && !wolf->flag_two)
		return (TTF_RenderText_Blended(wolf->ttf.font, "New game", col));
	else if (i == 1 && wolf->flag_two)
		return (TTF_RenderText_Blended(wolf->ttf.font, "  Resume", col));
	else if (i == 2)
		return (TTF_RenderText_Blended(wolf->ttf.font, "  Controls", col));
	else if (i == 0 && !wolf->flag_two)
		return (TTF_RenderText_Blended(wolf->ttf.font, "     ->"
		"Choose map here<-", col));
	else if (i == 0)
		return (TTF_RenderText_Blended(wolf->ttf.font, "Choose map and "
		"retry here", col));
	else
		return (TTF_RenderText_Blended(wolf->ttf.font, "     Exit", col));
}

void		draw_text(t_wolf *wolf, int width, int height, int i)
{
	SDL_Surface		*surface;
	int				*pixels;
	int				x;
	int				y;
	SDL_Color		col;

	get_rgb_from_int(&col.r, &col.g, &col.b, 16777215);
	surface = text_for_button(wolf, i, col);
	pixels = (int*)surface->pixels;
	y = -1;
	while (++y < surface->h * 0.2)
	{
		x = -1;
		while (++x < surface->w * 0.2)
		{
			if (pixels[(int)(x / 0.2) + (int)(y / 0.2) * surface->w] >> 24 != 0)
				sdl_put_pixel(&(t_point){x + width * 1.5, y + height, 0, pixels
				[(int)(x / 0.2) + (int)(y / 0.2) * surface->w]}, &wolf->sdl);
		}
	}
	SDL_FreeSurface(surface);
}

void		draw_buttons(t_wolf *wolf)
{
	int		height;
	int		width;
	int		x;
	int		y;
	int		i;

	i = 1;
	height = WIN_HEIGHT / 7;
	width = WIN_WIDTH / 4;
	while (i < 4)
	{
		y = height + (i - 1) * 2 * height - 1;
		while (++y < height * 2 * i)
		{
			x = width - 1;
			while (++x < width * 3)
				wolf->sdl.pixels[x + y * WIN_WIDTH] = 0;
		}
		draw_text(wolf, x - 2 * width, y - height, i);
		i++;
	}
	draw_text(wolf, x - 2.55 * width, height * 6, 0);
}

void		main_menu(t_wolf *wolf)
{
	int		x;
	int		y;

	y = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			wolf->sdl.pixels[x + y * WIN_WIDTH] = 7667733;
			x++;
		}
		y++;
	}
	draw_buttons(wolf);
}

void		choose_map(t_wolf *wolf, int i)
{
	if (wolf->flag == 3)
	{
		clean_map(wolf);
		if (i == 1)
			wolf->map = get_map("maps/map1");
		else if (i == 2)
			wolf->map = get_map("maps/map2");
		else if (i == 3)
			wolf->map = get_map("maps/map6");
		else if (i == 4)
			wolf->map = get_map("maps/map4");
		else if (i == 5)
			wolf->map = get_map("maps/map5");
		else
			wolf->map = get_map("maps/map7");
		wolf_init(wolf);
		render(wolf);
	}
}
