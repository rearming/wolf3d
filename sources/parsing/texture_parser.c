/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/18 19:57:34 by sleonard         ###   ########.fr       */
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
	int			i;
	int			j;

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
			sprite.data[sprite.height][sprite.width] =
					get_color_from_tilemap(img, j, i);
			j++;
			sprite.width++;
		}
		sprite.height++;
		i++;
	}
	return (sprite);
}

int			get_weapon(const char **files, int start,
			   t_weapon *weapon, int size)
{
	t_img			img;
	int				i;

	i = 0;
	if (!(weapon->sprite =
			(t_sprite*)malloc(sizeof(t_sprite) * weapon->frames)))
		raise_error(ERR_MALLOC);
	while (i < weapon->frames)
	{
		get_tilemap_data(&img, files[i + start]);
		weapon->sprite[i] = get_sprite(img, size, (t_point) {0, 0});
		free(img.data);
		i++;
	}
	return (weapon->frames);
}

void			get_all_weapons(const char **files, t_weapon *weapons)
{
	int		file_num;

	file_num = 3;
	weapons[0] = (t_weapon){GUN, 0,
				(t_point) {WIN_WIDTH / 3 + 100, WIN_HEIGHT / 2}, 6, 90, 2};
	weapons[1] = (t_weapon){KNIFE, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 4, 100, 4};
	weapons[2] = (t_weapon){DAKKA, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 11, 70, 4};
	weapons[3] = (t_weapon){PICKAXE, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 1, 70, 4};
	file_num += get_weapon(files, file_num, &weapons[0], 256);
	file_num += get_weapon(files, file_num, &weapons[1], 192);
	file_num += get_weapon(files, file_num, &weapons[2], 192);
	printf("filenum: [%i], name: [%s]\n", file_num, files[file_num]);
	file_num += get_weapon(files, file_num, &weapons[3], 200);
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
	textures.wood = get_sprite(img, 64, (t_point){0, 576});

	/*textures.sva_flag = get_sprite(img, 16, (t_point) {32, 48});
	textures.rock_wall = get_sprite(img, 16, (t_point) {112, 112});
	textures.hitler = get_sprite(img, 16, (t_point) {32, 0});
	textures.red_bricks = get_sprite(img, 16, (t_point) {48, 32});
	textures.sva_eagle = get_sprite(img, 16, (t_point) {192, 48});
	textures.wood = get_sprite(img, 16, (t_point) {64, 0});*/

	free(img.data);
	get_all_weapons(files, textures.weapons);

	return (textures);
}
