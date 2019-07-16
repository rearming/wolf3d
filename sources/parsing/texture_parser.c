/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/16 13:32:32 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		get_color_from_tilemap(t_img img, int j, int i)
{
	return (get_int_from_rgb(
			img.data[j * img.bpp + i * img.bpp * img.width],
			img.data[(j * img.bpp +
			i * img.bpp * img.width) + 1],
			img.data[(j * img.bpp +
			i * img.bpp * img.width) + 2],
			img.bpp > 3 ? img.data
			[j * img.bpp + i * img.bpp * img.width] : 255));
}

t_sprite		get_sprite(t_img img, int sprite_size, t_point sprite_pos)
{
	t_sprite	sprite;
	int 		i;
	int 		j;

	i = sprite_pos.y;
	sprite.bpp = img.bpp;
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
				= get_color_from_tilemap(img, j, i);
			j++;
			sprite.width++;
		}
		sprite.height++;
		i++;
	}
	return (sprite);
}

void			get_weapon(const char **files, int start, t_weapon *weapon, int size)
{
	t_img			img;
	int 			i;

	i = 0;
	if (!(weapon->sprite = (t_sprite*)malloc(sizeof(t_sprite) * weapon->frames)))
		raise_error(ERR_MALLOC);
	while (i < weapon->frames)
	{
		get_tilemap_data(&img, files[i + start]);
		weapon->sprite[i] = get_sprite(img, size, (t_point) {0, 0});
		free(img.data);
		i++;
	}
}

t_textures		get_all_textures(const char **files, int files_num)
{
	t_textures		textures;
	t_img			img;

	get_tilemap_data(&img, files[2]);
	textures.sva_flag = get_sprite(img, 64, (t_point) {256, 0});
	textures.rock_wall = get_sprite(img, 64, (t_point) {128, 0});
	textures.hitler = get_sprite(img, 64, (t_point) {128, 196});
	textures.red_bricks = get_sprite(img, 64, (t_point) {128, 320});
	textures.sva_eagle = get_sprite(img, 64, (t_point) {320, 64});
	free(img.data);
	textures.weapon[0] = (t_weapon){GUN, 0, (t_point) {WIN_WIDTH / 3 + 100, WIN_HEIGHT / 2}, 6, 90};
	textures.weapon[1] = (t_weapon){KNIFE, 0, (t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 4, 100};
	textures.weapon[2] = (t_weapon){GUN, 0, (t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 11, 70};
	get_weapon(files, 3, &textures.weapon[0], 256);
	get_weapon(files, 3 + 6, &textures.weapon[1], 192);
	get_weapon(files, 3 + 6 + 5, &textures.weapon[2], 192);
	return (textures);
}
