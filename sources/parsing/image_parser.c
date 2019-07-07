/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:59:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/12 22:09:05 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		print_bmp_params(t_wolf *wolf)
{
	printf("offset of data: [%i]\n", wolf->bmp.offset);
	printf("bmp file size: [%li]\n", wolf->bmp.file_size);
	printf("bmp bpp: [%i]\n", wolf->bmp.bpp);
	printf("bmp image size: [%li]\n", wolf->bmp.img_size);

}

int			get_bmp_title(t_wolf *wolf, FILE *file)
{
	char 	buff[4];
	int 	offset;

	fread(buff, sizeof(short), 1, file);
	fread(buff, sizeof(int), 1, file);
	wolf->bmp.file_size = *((int*)(buff));
	fread(buff, sizeof(int), 1, file);
	fread(buff, sizeof(int), 1, file);
	wolf->bmp.offset = *((int*)(buff));
	return (14);
}

void		get_bmp_image(t_wolf *wolf, char *filename)
{
	int 			i;
	int 			offset;
	FILE			*file;

	file = fopen(filename, "rb");
	offset = get_bmp_title(wolf, file);
	wolf->bmp.data = (unsigned char *)malloc(wolf->bmp.file_size);
	i = 0;
	while (fread(&wolf->bmp.data[i], sizeof(char), 1, file) && i < wolf->bmp.offset - offset)
		i++;
	wolf->bmp.width = *((int*)(wolf->bmp.data + 18 - offset));
	wolf->bmp.height = *((int*)(wolf->bmp.data + 22 - offset));
	wolf->bmp.bpp = *((int*)(wolf->bmp.data + 28 - offset)) / 8;
	wolf->bmp.color_used = *((int*)(wolf->bmp.data + 46 - offset));
	wolf->bmp.img_size = *((int*)(wolf->bmp.data + 34 - offset));
	//wolf->bmp.table = (int*)malloc(sizeof(int) * 256); // todo where is table?
	//fread(wolf->bmp.table, sizeof(int), sizeof(int) * 256, file);
	i = wolf->bmp.img_size - 2;
	while (fread(&wolf->bmp.data[i], sizeof(char), 1, file))
		i--;
}

void		get_image_stbi(t_wolf *wolf, char *filename)
{
	wolf->stb.data = stbi_load(filename, &wolf->stb.x, &wolf->stb.y, &wolf->stb.bpp, 0);
	printf("filename: [%s], width: [%i], height: [%i], channels: [%i]\n",
		   filename, wolf->stb.x, wolf->stb.y, wolf->stb.bpp);
}

void		get_image_data(t_wolf *wolf)
{
	//get_bmp_image(wolf, wolf->stb.filename);
	get_image_stbi(wolf, wolf->stb.filename);
}
