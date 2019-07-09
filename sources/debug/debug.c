/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:21:00 by rearming          #+#    #+#             */
/*   Updated: 2019/07/09 13:35:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		print_bmp_params(t_bmp bmp)
{
	printf("offset of data: [%i]\n", bmp.offset);
	printf("bmp file size: [%li]\n", bmp.file_size);
	printf("bmp bpp: [%i]\n", bmp.bpp);
	printf("bmp size: [%li]\n", bmp.img_size);
}

/*void		print_bytes(t_stb image)
{
	int 		y;
	int 		x;
	long 		count;

	count = 0;
	y = 0;
	while (y < image.height * 4)
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
}*/

void 		print_bmp(t_bmp bmp, t_sdl sdl)
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
	while (i < bmp.img_size)
	{
		if (bmp.color_used == 0)
		{
			r = bmp.data[i];
			g = bmp.data[i + 1];
			b = bmp.data[i + 2];
		}
		else
			get_rgb_from_int(&r, &g, &b, bmp.table[bmp.data[i]]);
		SDL_SetRenderDrawColor(sdl.rend, r, g, b, a);
		if (i % (bmp.width * bmp.bpp) == 0 && i)
		{
			x = 0;
			y++;
		}
		x++;
		i += bmp.bpp;
	}
}

void		print_texture(t_sdl sdl, int width, int height, int **data,
				   t_point print_coord)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			sdl_put_pixel((t_point){j + print_coord.x, i + print_coord.y,
						   0, data[i][j]}, sdl);
			j++;
		}
		i++;
	}
}
