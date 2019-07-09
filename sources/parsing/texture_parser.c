/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 13:43:21 by sleonard         ###   ########.fr       */
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

int			**get_sprite(t_stb img, t_point sprite, int sprite_size)
{
	int 	x;
	int 	y;
	int 	i;
	int 	j;
	int 	**res_sprite;

	i = sprite.y;
	y = 0;
	res_sprite = (int**)malloc(sizeof(int*) * (sprite_size));
	while (i < sprite.y + sprite_size)
	{
		j = sprite.x;
		x = 0;
		res_sprite[y] = (int*)malloc(sizeof(int) * (sprite_size));
		while (j < sprite.x + sprite_size)
		{
			res_sprite[y][x] = get_color_from_tilemap(img, i, j);
			j++;
			x++;
		}
		y++;
		i++;
	}
	return (res_sprite);
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
		textures.hitler = get_sprite(stb, (t_point){128, 196}, 64);
		textures.red_bricks = get_sprite(stb, (t_point){128, 320}, 64);
		textures.eagle_svaston = get_sprite(stb, (t_point){320, 64}, 64);
	}
	return (textures);
}