/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:21:00 by rearming          #+#    #+#             */
/*   Updated: 2019/07/07 12:21:06 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
		//printf("%i %i %i %i\t", r, g, b, a);
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
