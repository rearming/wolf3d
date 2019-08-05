/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 21:45:50 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 12:18:44 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				get_all_weapons(const char **files, t_anim *weapons)
{
	int		last_file;

	last_file = 0;
	weapons[0] = (t_anim){GUN, 0, (t_point) {WIN_WIDTH / 3 + 100,
							WIN_HEIGHT - 256 * 2}, 6, 0.013, 2};
	weapons[1] = (t_anim){KNIFE, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT - 192 * 4}, 4, 0.011, 4};
	weapons[2] = (t_anim){DAKKA, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT - 192 * 4}, 11, 0.02, 4};
	weapons[3] = (t_anim){PICKAXE, 0,
				(t_point) {WIN_WIDTH / 3, WIN_HEIGHT - 200 * 4}, 1, 0.01, 4};
	last_file += get_animation(files, last_file, &weapons[0], 256);
	last_file += get_animation(files, last_file, &weapons[1], 192);
	last_file += get_animation(files, last_file, &weapons[2], 192);
	last_file += get_animation(files, last_file, &weapons[3], 200);
	return (last_file);
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

int				get_player_head(const char **files, t_anim *head, int last_file)
{
	head->type = HEAD;
	head->scale = 0.2;
	head->frames = 4;
	head->frequency = 0.003;
	return (get_animation(files, last_file, head, 190));
}
