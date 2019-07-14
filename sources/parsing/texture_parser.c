/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/14 16:03:28 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int get_color_from_tilemap(t_stb img, t_bmp bmp_img, int j, int i)
{
	if (img.data)
	{
		return (get_int_from_rgb(
				img.data[j * img.bpp + i * img.bpp * img.width],
				img.data[(j * img.bpp +
						  i * img.bpp * img.width) + 1],
				img.data[(j * img.bpp +
						  i * img.bpp * img.width) + 2]));
	}
	return (get_int_from_rgb(
			bmp_img.data[j * bmp_img.bpp + i * bmp_img.bpp * bmp_img.width],
			bmp_img.data[(j * bmp_img.bpp +
					  i * bmp_img.bpp * bmp_img.width) + 1],
			bmp_img.data[(j * bmp_img.bpp +
					  i * bmp_img.bpp * bmp_img.width) + 2]));
}

t_sprite 	get_sprite(t_stb img, t_bmp bmp_img, int sprite_size, t_point sprite_pos)
{
	t_sprite	sprite;
	int 		i;
	int 		j;

	i = sprite_pos.y;
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
				= get_color_from_tilemap(img, bmp_img, j, i);
			j++;
			sprite.width++;
		}
		sprite.height++;
		i++;
	}
	return (sprite);
}

t_textures	get_all_textures(const char *filename)
{
	t_textures		textures;
	t_bmp			bmp;
	t_stb			stb;

	get_tilemap_data(&bmp, &stb, filename);
	textures.sva_flag = get_sprite(stb, bmp, 64, (t_point) {256, 0});
	textures.rock_wall = get_sprite(stb, bmp, 64, (t_point) {128, 0});
	textures.hitler = get_sprite(stb, bmp, 64, (t_point) {128, 196});
	textures.red_bricks = get_sprite(stb, bmp, 64, (t_point) {128, 320});
	textures.sva_eagle = get_sprite(stb, bmp, 64, (t_point) {320, 64});
	textures.size = 64;
	if (stb.data)
		free(stb.data);
	else
		free(bmp.data);
	return (textures);
}
