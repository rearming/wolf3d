/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:42:55 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/12 22:08:50 by sleonard         ###   ########.fr       */
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
	a = 255;
	SDL_SetRenderDrawColor(wolf->sdl.rend, r, g, b, a);
	SDL_RenderDrawPoint(wolf->sdl.rend, point.x, point.y);
}

void		parse_color(int *r, int *g, int *b, int color)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

void		print_bytes(t_stb image)
{
	int 		y;
	int 		x;
	long 		count;

	count = 0;
	y = 0;
	while (y < image.y * 4)
	{
		x = 0;
		while (x < image.x * 4)
		{
			printf("%i ", image.data[x + y * image.x]);
			if ((x + 1) % 4 == 0 && x)
				printf("  ");
			count++;
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n\n number of bytes: [%li]\n", count);
}

void		print_bmp(t_wolf *wolf)
{
	int 		i;
	int 		x;
	int 		y;

	int 		r;
	int 		g;
	int 		b;
	int 		a;

	i = 0;
	x = 0;
	y = 0;
	a = 255;
	printf("%d %d\n",wolf->bmp.width, wolf->bmp.height);
	while (i < wolf->bmp.img_size)
	{
		if (wolf->bmp.color_used == 0) // todo if color table needed
		{
			r = wolf->bmp.data[i];
			g = wolf->bmp.data[i + 1];
			b = wolf->bmp.data[i + 2];
		}
		else
			parse_color(&r, &g, &b, wolf->bmp.table[wolf->bmp.data[i]]);
		SDL_SetRenderDrawColor(wolf->sdl.rend, r, g, b, a);
		SDL_RenderDrawPoint(wolf->sdl.rend, x + wolf->offset_x, y + wolf->offset_y);
		if (i % (wolf->bmp.width * wolf->bmp.bpp) == 0 && i)
		{
			x = 0;
			y++;
		}
		x++;
		i += wolf->bmp.bpp;
	}
}

void		print_image(t_wolf *wolf)
{
	int 		i;
	int 		x;
	int 		y;

	int 		r;
	int 		g;
	int 		b;
	int 		a;

	i = 0;
	x = 0;
	y = 0;
	a = 255;
	while (i < wolf->stb.y * wolf->stb.x * wolf->stb.bpp)
	{
		r = wolf->stb.data[i];
		g = wolf->stb.data[i + 1];
		b = wolf->stb.data[i + 2];
		if (wolf->stb.bpp > 3)
			a = wolf->stb.data[i + 3];
		//printf("%i %i %i %i\n", r, g, b, a);
		SDL_SetRenderDrawColor(wolf->sdl.rend, r, g, b, a);
		SDL_RenderDrawPoint(wolf->sdl.rend, x + wolf->offset_x, y + wolf->offset_y);
		if (i % (wolf->stb.x * wolf->stb.bpp) == 0 && i)
		{
			//printf("\n");
			x = 0;
			y++;
		}
		x++;
		i += wolf->stb.bpp;
	}
}

void		get_image_data(t_wolf *wolf)
{
	get_bmp_image(wolf, wolf->stb.filename);
	//get_image_stbi(wolf, wolf->stb.filename);
}

void		render(t_wolf *wolf)
{
	SDL_SetRenderDrawColor(wolf->sdl.rend, 0, 0, 0, 0);
	SDL_RenderClear(wolf->sdl.rend);
	print_bmp(wolf);
	//print_image(wolf);
	SDL_RenderPresent(wolf->sdl.rend);
	print_bmp_params(wolf);
}