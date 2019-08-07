/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:10:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/07 16:03:42 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
		else if (term->parsed_command[2] == WOLF3D)
			wolf->textures.texture_type = WOLF3D;
		else if (term->parsed_command[2] == COMPASS_MODE)
			wolf->textures.render_mode = COMPASS_MODE;
		else if (term->parsed_command[2] == INDEX_MODE)
			wolf->textures.render_mode = INDEX_MODE;
	}
}

void	process_player_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == LOOK)
	{
		if (term->parsed_command[2] == FREEZE)
			wolf->player.look_frozen = TRUE;
		if (term->parsed_command[2] == UNFREEZE)
			wolf->player.look_frozen = FALSE;
	}
	if (term->parsed_command[1] == TELEPORT)
		teleport_player(wolf, term);
}

void	process_change_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == CHANNELS)
		change_channels(wolf, term);
}

void	process_full_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[0] == RENDER)
		process_render_command(wolf, term);
	if (term->parsed_command[0] == SET)
		process_set_command(wolf, term);
	if (term->parsed_command[0] == CHANGE)
		process_change_command(wolf, term);
	if (term->parsed_command[0] == PLAYER)
		process_player_command(wolf, term);
}
