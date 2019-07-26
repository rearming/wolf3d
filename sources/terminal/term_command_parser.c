/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_command_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:17:08 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 17:37:57 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		parse_command_type(t_erm *term)
{
	if (term->cmd_i != 0)
		return ;
	if (ft_strequ(term->command[0], "render"))
		term->parsed_command[0] = RENDER;
	if (ft_strequ(term->command[0], "set"))
		term->parsed_command[0] = SET;
}

void		parse_command_target(t_erm *term)
{
	if (term->cmd_i != 1)
		return ;
	if (ft_strequ(term->command[1], "all"))
		term->parsed_command[1] = ALL;
	if (ft_strequ(term->command[1], "block"))
		term->parsed_command[1] = BLOCK;
}

void		parse_command_content(t_erm *term)
{
	if (term->cmd_i != 2)
		return ;
	else if (ft_strequ(term->command[2], "minecraft"))
		term->parsed_command[2] = MINECRAFT;
	else if (ft_strequ(term->command[2], "wolf"))
		term->parsed_command[2] = WOLF3D;
	else if (ft_strequ(term->command[2], "compass"))
		term->parsed_command[2] = COMPASS_MODE;
	else if (ft_strequ(term->command[2], "index"))
		term->parsed_command[2] = INDEX_MODE;
	else
		term->parsed_command[2] = ft_atoi(term->command[2]);
}

void	parse_command(t_wolf *wolf, t_erm *term)
{
	while (term->command[term->cmd_i])
	{
		parse_command_type(term);
		parse_command_target(term);
		parse_command_content(term);
		term->cmd_i++;
	}
	process_full_command(wolf, term);
}
