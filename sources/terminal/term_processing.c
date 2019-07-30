/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:10:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/30 12:33:32 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_index(int texture_type, int index)
{
	if (index > 0)
	{
		if (texture_type == MINECRAFT && index >= MINE_SPRITES)
			return (0);
		else if (texture_type == WOLF3D && index >= WOLF_SPRITES)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	change_block_index(t_wolf *wolf, t_erm *term)
{
	t_ray	ray;
	int		index;

	ray = raycast(wolf, wolf->player.angle);
	index = term->parsed_command[2];
	if (check_index(wolf->textures.texture_type, index))
		wolf->map.int_map[(int)ray.y][(int)ray.x] = term->parsed_command[2];
}

void	change_all_blocks(t_wolf *wolf, t_erm *term)
{
	int		y;
	int		x;
	int		index;

	index = term->parsed_command[2];
	if (!check_index(wolf->textures.texture_type, index))
		return ;
	y = 0;
	while (y < wolf->map.height)
	{
		x = 0;
		while (x < wolf->map.width)
		{
			if (wolf->map.int_map[y][x] > 0)
				wolf->map.int_map[y][x] = term->parsed_command[2];
			x++;
		}
		y++;
	}
}

void	process_set_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == BLOCK)
		change_block_index(wolf, term);
	if (term->parsed_command[1] == ALL)
		change_all_blocks(wolf, term);
}

void	process_render_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == ALL)
	{
		if (term->parsed_command[2] == MINECRAFT)
			wolf->textures.texture_type = MINECRAFT;
		if (term->parsed_command[2] == WOLF3D)
			wolf->textures.texture_type = WOLF3D;
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
