/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/15 16:36:42 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int get_color_from_tilemap(t_stb stb_img, t_bmp bmp_img, int j, int i)
{
	if (stb_img.data)
	{
		return (get_int_from_rgb(
				stb_img.data[j * stb_img.bpp + i * stb_img.bpp * stb_img.width],
				stb_img.data[(j * stb_img.bpp +
						  i * stb_img.bpp * stb_img.width) + 1],
				stb_img.data[(j * stb_img.bpp +
						  i * stb_img.bpp * stb_img.width) + 2]));
	}
	return (get_int_from_rgb(
			bmp_img.data[j * bmp_img.bpp + i * bmp_img.bpp * bmp_img.width],
			bmp_img.data[(j * bmp_img.bpp +
					  i * bmp_img.bpp * bmp_img.width) + 1],
			bmp_img.data[(j * bmp_img.bpp +
					  i * bmp_img.bpp * bmp_img.width) + 2]));
}

t_sprite 	get_sprite(t_stb stb_img, t_bmp bmp_img, int sprite_size, t_point sprite_pos)
{
	t_sprite	sprite;
	int 		i;
	int 		j;

	i = sprite_pos.y;
	sprite.bpp = stb_img.data ? stb_img.bpp : bmp_img.bpp;
	sprite.size = sprite_size;
	sprite.height = 0;
	sprite.data = (int**)malloc(sizeof(int*) * (sprite_size));
	while (i < sprite_pos.y + sprite_size)
	{
		j = sprite_pos.x;
		sprite.width = 0;
		sprite.data[sprite.height] = (int*)malloc(sizeof(int) * (sprite_size));
		while (j < sprite_pos.x + sprite_size)
		{
			sprite.data[sprite.height][sprite.width]
				= get_color_from_tilemap(stb_img, bmp_img, j, i);
			j++;
			sprite.width++;
		}
		sprite.height++;
		i++;
	}
	return (sprite);
}

void		free_img_data(t_stb *stb_img, t_bmp *bmp_img)
{
	if (stb_img->data)
		free(stb_img->data);
	if (stb_img->data)
		free(bmp_img->data);
}

t_textures get_all_textures(const char **files, int files_num)
{
	t_textures		textures;
	t_bmp			bmp_img;
	t_stb			stb_img;
	int 			i;

	get_tilemap_data(&bmp_img, &stb_img, files[2]);
	textures.sva_flag = get_sprite(stb_img, bmp_img, 64, (t_point) {256, 0});
	textures.rock_wall = get_sprite(stb_img, bmp_img, 64, (t_point) {128, 0});
	textures.hitler = get_sprite(stb_img, bmp_img, 64, (t_point) {128, 196});
	textures.red_bricks = get_sprite(stb_img, bmp_img, 64, (t_point) {128, 320});
	textures.sva_eagle = get_sprite(stb_img, bmp_img, 64, (t_point) {320, 64});
	free_img_data(&stb_img, &bmp_img);
	i = 0;
	while (i < files_num)
	{
		get_tilemap_data(&bmp_img, &stb_img, files[i + 3]);
		textures.pistol[i] = get_sprite(stb_img, bmp_img, 256, (t_point) {0, 0});
		i++;
	}
	return (textures);
}
