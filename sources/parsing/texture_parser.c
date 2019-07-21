/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/21 10:37:34 by rearming         ###   ########.fr       */
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
			[(j * img.bpp + i * img.bpp * img.width) + 3] : 255));
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

int				get_animation(const char **files, int start,
								 t_anim *weapon, int size)
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

int				get_all_weapons(const char **files, t_anim *weapons)
{
	int		last_file;

	last_file = START_OF_WEAPONS;
	weapons[0] = (t_anim){GUN, 0,
				(t_point) {WIN_WIDTH / 3 + 100, WIN_HEIGHT / 2}, 6, 90, 2};
	weapons[1] = (t_anim){KNIFE, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 4, 100, 4};
	weapons[2] = (t_anim){DAKKA, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 11, 70, 4};
	weapons[3] = (t_anim){PICKAXE, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT / 4}, 1, 70, 4};
	last_file += get_animation(files, last_file, &weapons[0], 256);
	last_file += get_animation(files, last_file, &weapons[1], 192);
	last_file += get_animation(files, last_file, &weapons[2], 192);
	printf("filenum: [%i], name: [%s]\n", last_file, files[last_file]);
	last_file += get_animation(files, last_file, &weapons[3], 200);
	return (last_file);
}

t_sprite		*get_all_sprites(const char *filename,
		int sprite_size, int sprites_number)
{
	t_sprite	*sprites;
	t_img		img;
	int			i;
	int	 		x;
	int			y;

	if (!(sprites = (t_sprite*)malloc(sizeof(t_sprite) * sprites_number)))
		raise_error(ERR_MALLOC);
	x = 0;
	y = 0;
	i = 0;
	get_tilemap_data(&img, filename);
	while (i < sprites_number)
	{
		if (x == img.width)
		{
			y += sprite_size;
			x = 0;
		}
		sprites[i] = get_sprite(img, sprite_size, (t_point){x, y});
		i++;
		x += sprite_size;
	}
	free(img.data);
	return (sprites);
}

t_sprite		*get_minecraft_art(const char *filename)
{
	t_img		img;
	t_sprite	*pictures;

	if (!(pictures = (t_sprite*)malloc(sizeof(t_sprite) * 8)))
		raise_error(ERR_MALLOC);
	get_tilemap_data(&img, filename);
	pictures[0] = get_sprite(img, 32, (t_point){0, 128});
	pictures[1] = get_sprite(img, 32, (t_point){32, 128});
	pictures[2] = get_sprite(img, 32, (t_point){64, 128});
	pictures[3] = get_sprite(img, 32, (t_point){96, 128});
	pictures[4] = get_sprite(img, 32, (t_point){128, 128});

	pictures[5] = get_sprite(img, 64, (t_point){0, 192});
	pictures[6] = get_sprite(img, 64, (t_point){64, 192});
	pictures[7] = get_sprite(img, 64, (t_point){128, 192});
	free(img.data);
	return (pictures);
}

int 			get_player_head(const char **files, t_anim *head, int last_file)
{
	head->scale = 0.2;
	head->frames = 4;
	head->frequency = 300;
	return (get_animation(files, last_file, head, 190));
}

t_textures		get_all_textures(const char **files, int files_num)
{
	t_textures		textures;
	t_img			img;
	int 			last_file;

	last_file = 0;
	if (!(textures.sprites = (t_sprite**)malloc(sizeof(t_sprite*) * TILEMAPS)))
		raise_error(ERR_MALLOC);
	textures.sprites[WOLF3D] = get_all_sprites(files[2], 64, WOLF_SPRITES);
	textures.sprites[MINECRAFT] = get_all_sprites(files[3], 16, MINE_SPRITES);
	textures.sprites[MINECRAFT_ART] = get_minecraft_art(files[4]);
	last_file += get_all_weapons(files, textures.weapons);
	last_file += get_player_head(files, &textures.head, last_file);
	return (textures);
}
