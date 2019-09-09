/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:09:32 by bbear             #+#    #+#             */
/*   Updated: 2019/09/09 20:38:47 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface *text_for_button(t_wolf *wolf, int i, SDL_Color col)
{
    if (i == 1 && !wolf->flag_two)
        return (TTF_RenderText_Blended(wolf->ttf.font, "New game", col));
    else if (i == 1 && wolf->flag_two)
        return (TTF_RenderText_Blended(wolf->ttf.font, "  Resume", col));
    else if (i == 2)
        return (TTF_RenderText_Blended(wolf->ttf.font, "  Controls", col));
    else
        return (TTF_RenderText_Blended(wolf->ttf.font, "     Exit", col));
}

void    draw_text(t_wolf *wolf, int width, int height, int i)
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
    while (++y < surface->h*0.2)
    {
        x = -1;
        while (++x < surface->w*0.2)
        {
            if (pixels[(int)(x / 0.2) + (int)(y / 0.2) * surface->w] >> 24 != 0)
                sdl_put_pixel(&(t_point){x + width * 1.5, y + height, 0,pixels
                [(int)(x / 0.2) + (int)(y / 0.2) * surface->w]}, &wolf->sdl);
        }
    }
    SDL_FreeSurface(surface);
}

void    draw_buttons(t_wolf *wolf)
{
    int     height;
    int     width;
    int     x;
    int     y;
    int     i;

    i = 1;
    height = WIN_HEIGHT / 7;
    width = WIN_WIDTH / 4;
    while (i < 4)
    {
        y = height + (i - 1) * 2 * height;
        while (y < height * 2 * i)
        {
            x = width;
            while (x < width * 3)
            {
                wolf->sdl.pixels[x + y * WIN_WIDTH] = 0;//200 * 255 * 255 + 255 * 1 + 255;
                x++;
            }
            y++;
        }
        draw_text(wolf, x - 2 * width, y - height, i);
        i++;
    }
}

void    main_menu(t_wolf *wolf)
{
    int     x;
    int     y;

    y = 0;
    SDL_SetRelativeMouseMode(SDL_FALSE);
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            wolf->sdl.pixels[x + y * WIN_WIDTH] = 176 * 255 * 255 + 128 * 255 + 255;
            x++;
        }
        y++;
    }
    draw_buttons(wolf);
}