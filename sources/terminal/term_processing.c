/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:10:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 16:26:29 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	change_single_block(t_wolf *wolf, t_erm *term)
{
	t_ray	ray;

	ray = raycast(wolf, wolf->player.angle);
	wolf->map.int_map[(int)ray.y][(int)ray.x] == term->parsed_command[]
}

void	process_set_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == BLOCK)
	{
		change_single_block(wolf, term);
	}
}

void	process_render_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == ALL)
	{
		if (term->parsed_command[2] == MINECRAFT)
			wolf->textures.texture_mode = MINECRAFT;
		if (term->parsed_command[2] == WOLF3D)
			wolf->textures.texture_mode = WOLF3D;
		if (term->parsed_command[2] == COMPASS_MODE)
			wolf->textures.render_mode = COMPASS_MODE;
		if (term->parsed_command[2] == INDEX_MODE)
			wolf->textures.render_mode = INDEX_MODE;
	}
}

void	process_full_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[0] == RENDER)
		process_render_command(wolf, term);
	if (term->parsed_command[0] == SET)
		process_set_command(wolf, term);
}
