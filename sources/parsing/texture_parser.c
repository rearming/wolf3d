/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 10:06:20 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int 	get_color_from_tilemap(t_stb img, int i, int j)
{
	return (get_int_from_rgb(
			img.data[j * img.bpp + i * img.bpp * img.width],
			img.data[(j * img.bpp +
					  i * img.bpp * img.width) + 1],
			img.data[(j * img.bpp +
					  i * img.bpp * img.width) + 2]));
}

t_sprite	get_sprite(t_stb img, t_point sprite_pos, int sprite_size)
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
				= get_color_from_tilemap(img, i, j);
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
	int 			img_type;

	img_type = get_tilemap_data(&bmp, &stb, filename);
	if (img_type == STB_IMG)
	{
		textures.sva_flag = get_sprite(stb, (t_point) {256, 0}, 64);
		textures.rock_wall = get_sprite(stb, (t_point) {128, 0}, 64);
		//textures.hitler = get_sprite(stb, (t_point){128, 196}, 64);
		textures.hitler = get_sprite(stb, (t_point){0, 1024}, 128);
		textures.red_bricks = get_sprite(stb, (t_point){128, 320}, 64);
		textures.sva_eagle = get_sprite(stb, (t_point){320, 64}, 64);
		free(stb.data);
	}
	return (textures);
}