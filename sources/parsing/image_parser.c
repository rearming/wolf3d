/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:59:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/23 16:19:51 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			get_bmp_title(t_img *bmp, FILE *file)
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

void		get_bmp_image(t_img *bmp, const char *filename)
{
	int 			i;
	int 			offset;
	FILE			*file;

	if (!(file = fopen(filename, "rb")))
		raise_error(ERR_INV_IMAGE);
	offset = get_bmp_title(bmp, file);
	bmp->data = (unsigned char *)malloc(bmp->file_size);
	i = 0;
	while (fread(&bmp->data[i], sizeof(char), 1, file)
		&& i < bmp->offset - offset)
		i++;
	bmp->width = *((int*)(bmp->data + 18 - offset));
	bmp->height = *((int*)(bmp->data + 22 - offset));
	bmp->bpp = *((int*)(bmp->data + 28 - offset)) / 8;
	bmp->img_size = *((int*)(bmp->data + 34 - offset));
	i = bmp->img_size - 2;
	while (fread(&bmp->data[i], sizeof(char), 1, file))
		i--;
}

void		get_tilemap_data(t_img *img, const char *filename)
{
	int 	filename_len;

	img->data = NULL;
	filename_len = ft_strlen(filename);
	if (filename_len > 3 && ft_strequ(&filename[filename_len - 4], ".bmp"))
		get_bmp_image(img, filename);
	if (!(img->data =
				stbi_load(filename, &img->width, &img->height, &img->bpp, 0)))
		raise_error(ERR_INV_IMAGE);
}
