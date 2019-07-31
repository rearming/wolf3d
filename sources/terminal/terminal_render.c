/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:53:12 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/31 20:07:56 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_term_input(t_erm *term, t_sdl *sdl, TTF_Font *font)
{
	SDL_Surface		*surface;
	int				*pixels;
	int				x;
	int				y;
	SDL_Color		col;

	get_rgb_from_int(&col.r, &col.g, &col.b, term->text_color);
	surface = TTF_RenderText_Blended(font, term->buffs[term->mem_i], col);
	pixels = (int*)surface->pixels;
	y = 0;
	while (y < surface->h * term->scale)
	{
		x = 0;
		while (x < surface->w * term->scale)
		{
			if (pixels[(int)(x / term->scale) + (int)(y / term->scale) * surface->w] >> 24 != 0)
				sdl_put_pixel(&(t_point){x + term->pos.x, y + term->pos.y, 0,
					pixels[(int)(x / term->scale) + (int)(y / term->scale) * surface->w]}, sdl);
			x++;
		}
		y++;
	}
	SDL_FreeSurface(surface);
}

void		draw_terminal(t_wolf *wolf)
{
	draw_term_input(&wolf->term, &wolf->sdl, wolf->ttf.font);
	bresen_line(wolf->sdl, (t_point) {0, WIN_HEIGHT - 200},
			(t_point){WIN_WIDTH, WIN_HEIGHT - 200}, wolf->term.line_color);
}
