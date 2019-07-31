/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:41:42 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/31 21:50:29 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sprite		*get_all_sprites(const char *filename,
		int sprite_size, int sprites_number)
{
	t_sprite	*sprites;
	t_img		img;
	t_point		pos;
	int			i;

	if (!(sprites = (t_sprite*)malloc(sizeof(t_sprite) * sprites_number)))
		raise_error(ERR_MALLOC);
	get_tilemap_data(&img, filename);
	if (img.width * img.height != sprites_number * pow(sprite_size, 2))
		raise_error(ERR_INV_IMAGE);
	i = 0;
	pos = (t_point){0, 0};
	while (i < sprites_number)
	{
		if (pos.x == img.width)
		{
			pos.y += sprite_size;
			pos.x = 0;
		}
		sprites[i] = get_sprite(img, sprite_size, (t_point){pos.x, pos.y});
		i++;
		pos.x += sprite_size;
	}
	free(img.data);
	return (sprites);
}

t_textures		get_all_textures(const char **files)
{
	t_textures		textures;
	int				last_file;

	last_file = 0;
	if (!(textures.sprites = (t_sprite**)malloc(sizeof(t_sprite*) * TILEMAPS)))
		raise_error(ERR_MALLOC);
	last_file += get_all_weapons(files, textures.weapons);
	last_file += get_player_head(files, &textures.head, last_file);
	textures.sprites[WOLF3D] =
			get_all_sprites(files[last_file], 64, WOLF_SPRITES);
	textures.sprites[MINECRAFT] =
			get_all_sprites(files[last_file + 1], 16, MINE_SPRITES);
	textures.sprites[MINECRAFT_ART] = get_minecraft_art(files[last_file + 2]);
	return (textures);
}
