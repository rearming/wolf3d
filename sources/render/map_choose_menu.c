/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_choose_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:32:55 by bbear             #+#    #+#             */
/*   Updated: 2019/09/15 16:31:47 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*draw_text_maps(t_wolf *wolf, int i, SDL_Color col)
{
	if (i == 1)
		return (TTF_RenderText_Blended(wolf->ttf.font, "1", col));
	else if (i == 2)
		return (TTF_RenderText_Blended(wolf->ttf.font, "4", col));
	else if (i == 3)
		return (TTF_RenderText_Blended(wolf->ttf.font, "2", col));
	else if (i == 4)
		return (TTF_RenderText_Blended(wolf->ttf.font, "5", col));
	else if (i == 5)
		return (TTF_RenderText_Blended(wolf->ttf.font, "3", col));
	else if (i == 6)
		return (TTF_RenderText_Blended(wolf->ttf.font, "6", col));
	else
		return (TTF_RenderText_Blended(wolf->ttf.font, "<- Back", col));
}

void		draw_text_at(t_wolf *wolf, int width, int height, int i)
{
	SDL_Surface		*surface;
	int				*pixels;
	int				x;
	int				y;
	SDL_Color		col;

	get_rgb_from_int(&col.r, &col.g, &col.b, 16777215);
	surface = draw_text_maps(wolf, i, col);
	pixels = (int*)surface->pixels;
	y = -1;
	while (++y < surface->h * 0.12)
	{
		x = -1;
		while (++x < surface->w * 0.12)
		{
			if (pixels[(int)(x / 0.12) + (int)(y / 0.12) *
			surface->w] >> 24 != 0)
				sdl_put_pixel(&(t_point){x + width, y + height, 0, pixels
				[(int)(x / 0.12) + (int)(y / 0.12) * surface->w]}, &wolf->sdl);
		}
	}
	SDL_FreeSurface(surface);
}

void		draw_buttons_map_two(t_wolf *wolf, int j)
{
	int		height;
	int		width;
	int		x;
	int		y;
	int		i;

	i = 0;
	height = WIN_HEIGHT / 6;
	width = WIN_WIDTH / 7;
	draw_text_at(wolf, WIN_WIDTH / 8 - 100, WIN_HEIGHT / 14, 0);
	while (++i < 3)
	{
		y = height * 2 + (i - 1) * 2 * height;
		while (y < height * (3 * i - (i - 1)))
		{
			x = width * (j + 1);
			while (x < width * (j + 2))
			{
				wolf->sdl.pixels[x + y * WIN_WIDTH] = 0;
				x++;
			}
			y++;
		}
		draw_text_at(wolf, x - 0.55 * width, y - 0.75 * height, i + j);
	}
}

void		draw_buttons_map(t_wolf *wolf)
{
	int		j;

	j = 0;
	while (j < 5)
	{
		draw_buttons_map_two(wolf, j);
		j += 2;
	}
}

void		maps_menu(t_wolf *wolf)
{
	int		x;
	int		y;

	y = 0;
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
	draw_back_button(wolf);
	draw_buttons_map(wolf);
}
