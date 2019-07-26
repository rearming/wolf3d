/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_command_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:17:08 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 15:22:05 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	process_render_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[1] == ALL)
	{
		if (term->parsed_command[2] == MINECRAFT)
			wolf->textures.texture_mode = MINECRAFT;
		if (term->parsed_command[2] == WOLF3D)
			wolf->textures.texture_mode = WOLF3D;
	}
	if (term->parsed_command[1] == COMPASS_MODE)
		wolf->textures.render_mode = COMPASS_MODE;
	if (term->parsed_command[1] == NUMBER_MODE)
		wolf->textures.render_mode = NUMBER_MODE;
}

void	process_full_command(t_wolf *wolf, t_erm *term)
{
	if (term->parsed_command[0] == RENDER)
		process_render_command(wolf, term);
}

void	parse_command(t_wolf *wolf, t_erm *term)
{
	if (ft_strequ(term->command[0], "render"))
		term->parsed_command[0] = RENDER;
	if (ft_strequ(term->command[1], "all"))
		term->parsed_command[1] = ALL;
	if (ft_strequ(term->command[1], "compass"))
		term->parsed_command[1] = COMPASS_MODE;
	if (ft_strequ(term->command[1], "number"))
		term->parsed_command[1] = NUMBER_MODE;
	if (ft_strequ(term->command[2], "minecraft"))
		term->parsed_command[2] = MINECRAFT;
	if (ft_strequ(term->command[2], "wolf"))
		term->parsed_command[2] = WOLF3D;
	process_full_command(wolf, term);
}
