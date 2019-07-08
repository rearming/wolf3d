/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:21:00 by rearming          #+#    #+#             */
/*   Updated: 2019/07/08 19:43:50 by sleonard         ###   ########.fr       */
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
	while (y < image.heigth * 4)
	{
		x = 0;
		while (x < image.width * 4)
		{
			printf("%i ", image.data[x + y * image.width]);
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
		if (i % (wolf->bmp.width * wolf->bmp.bpp) == 0 && i)
		{
			x = 0;
			y++;
		}
		x++;
		i += wolf->bmp.bpp;
	}
}

void		print_image(t_stb image, t_sdl sdl)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < image.heigth)
	{
		j = 0;
		while (j < image.width)
		{
			sdl_put_pixel((t_point){j, i, 0, image.sprite[i][j]}, sdl);
			j++;
		}
		i++;
	}
	printf("image.height: [%i] | width: [%i] | bpp: [%i]\n",
			image.heigth, image.width, image.bpp);
}
