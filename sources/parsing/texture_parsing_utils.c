/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 21:49:03 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/31 21:52:21 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				get_color_from_tilemap(t_img img, int j, int i)
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
		weapon->sprite[i] = get_sprite(img, size, (t_point) {0, 0, 0, 0});
		free(img.data);
		i++;
	}
	return (weapon->frames);
}
