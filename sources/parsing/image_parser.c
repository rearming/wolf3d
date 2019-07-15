/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:59:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/15 16:32:16 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			get_bmp_title(t_bmp *bmp, FILE *file)
{
	char 	buff[4];

	fread(buff, sizeof(short), 1, file);
	fread(buff, sizeof(int), 1, file);
	bmp->file_size = *((int*)(buff));
	fread(buff, sizeof(int), 1, file);
	fread(buff, sizeof(int), 1, file);
	bmp->offset = *((int*)(buff));
	return (14);
}

void		get_bmp_image(t_bmp *bmp, const char *filename)
{
	int 			i;
	int 			offset;
	FILE			*file;

	file = fopen(filename, "rb");
	offset = get_bmp_title(bmp, file);
	bmp->data = (unsigned char *)malloc(bmp->file_size);
	i = 0;
	while (fread(&bmp->data[i], sizeof(char), 1, file)
		&& i < bmp->offset - offset)
		i++;
	bmp->width = *((int*)(bmp->data + 18 - offset));
	bmp->height = *((int*)(bmp->data + 22 - offset));
	bmp->bpp = *((int*)(bmp->data + 28 - offset)) / 8;
	bmp->color_used = *((int*)(bmp->data + 46 - offset));
	bmp->img_size = *((int*)(bmp->data + 34 - offset));
	i = bmp->img_size - 2;
	while (fread(&bmp->data[i], sizeof(char), 1, file))
		i--;
}

void		get_tilemap_data(t_bmp *bmp, t_stb *stb, const char *filename)
{
	int 	filename_len;

	bmp->data = NULL;
	stb->data = NULL;
	filename_len = ft_strlen(filename);
	if (filename_len > 3 && ft_strequ(&filename[filename_len - 4], ".bmp"))
		get_bmp_image(bmp, filename);
	else
		stb->data =
				stbi_load(filename, &stb->width, &stb->height, &stb->bpp, 0);
}
