/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 17:46:17 by bbear             #+#    #+#             */
/*   Updated: 2019/09/13 13:20:35 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*draw_text_three(t_wolf *wolf, int i, SDL_Color col)
{
	if (i == 2)
		return (TTF_RenderText_Blended(wolf->ttf.font, "   W, A, S, D         "
		"      Move", col));
	else if (i == 3)
		return (TTF_RenderText_Blended(wolf->ttf.font, "      LMB "
		"                    Shot, break block", col));
	else if (i == 4)
		return (TTF_RenderText_Blended(wolf->ttf.font, "      RMB           "
		"          Set block", col));
	else if (i == 5)
		return (TTF_RenderText_Blended(wolf->ttf.font, "     : + Ctrl         "
		"         Call terminal", col));
	else if (i == 6)
		return (TTF_RenderText_Blended(wolf->ttf.font, "Mouse Wheel     "
		"     Change weapon", col));
	else
		return (TTF_RenderText_Blended(wolf->ttf.font, "<- Back     "
		"                      *CONTROLS*", col));
}

void		draw_text_two(t_wolf *wolf, int width, int height, int i)
{
	SDL_Surface		*surface;
	int				*pixels;
	int				x;
	int				y;
	SDL_Color		col;

	get_rgb_from_int(&col.r, &col.g, &col.b, 16777215);
	surface = draw_text_three(wolf, i, col);
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

void		draw_back_button(t_wolf *wolf)
{
	int		height;
	int		width;
	int		x;
	int		y;

	height = WIN_HEIGHT / 14;
	width = WIN_WIDTH / 8;
	y = height;
	while (y < height * 2)
	{
		x = width / 2;
		while (x < width * 2 - 100)
		{
			wolf->sdl.pixels[x + y * WIN_WIDTH] = 0;
			x++;
		}
		y++;
	}
}

void		draw_buttons_two(t_wolf *wolf)
{
	int		height;
	int		width;
	int		x;
	int		y;
	int		i;

	i = 1;
	height = WIN_HEIGHT / 14;
	width = WIN_WIDTH / 8;
	draw_text_two(wolf, width - 100, height, i);
	while (++i < 7)
	{
		y = height + (i - 1) * 2 * height;
		while (y < height * 2 * i)
		{
			x = width / 2;
			while (x < width * 3)
			{
				wolf->sdl.pixels[x + y * WIN_WIDTH] = 0;
				x++;
			}
			y++;
		}
		draw_text_two(wolf, x - 2 * width, y - height, i);
	}
}

void		controls(t_wolf *wolf)
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
	draw_buttons_two(wolf);
}
