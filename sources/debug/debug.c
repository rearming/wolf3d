/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:21:00 by rearming          #+#    #+#             */
/*   Updated: 2019/07/16 12:53:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		print_bmp_params(t_img bmp)
{
	printf("offset of data: [%i]\n", bmp.offset);
	printf("bmp file size: [%li]\n", bmp.file_size);
	printf("bmp bpp: [%i]\n", bmp.bpp);
}

/*void		print_bytes(t_img image)
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

void		print_texture(t_sdl sdl, int width, int height, int **data, t_point print_coord,
			  int bpp)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((data[i][j] >> 24) != 0)
				sdl_put_pixel((t_point) {j + print_coord.x, i + print_coord.y,
										 0, data[i][j]}, sdl);
			j++;
		}
		i++;
	}
}
