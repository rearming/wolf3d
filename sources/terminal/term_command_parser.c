/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_command_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:17:08 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/07 16:37:58 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		parse_command_type(t_erm *term, int cmd_num)
{
	if (term->cmd_i != 0 || cmd_num < 0)
		return (INV_COMMAND);
	if (ft_strequ(term->command[0], "render"))
		return (RENDER);
	if (ft_strequ(term->command[0], "set"))
		return (SET);
	if (ft_strequ(term->command[0], "player"))
		return (PLAYER);
	if (ft_strequ(term->command[0], "change"))
		return (CHANGE);
	return (INV_COMMAND);
}

int		parse_command_target(t_erm *term, int cmd_num)
{
	if (term->cmd_i != 1 || cmd_num < 1)
		return (INV_COMMAND);
	if (ft_strequ(term->command[1], "all"))
		return (ALL);
	else if (ft_strequ(term->command[1], "colors"))
		return (COLORS);
	else if (ft_strequ(term->command[1], "channels"))
		return (CHANNELS);
	else if (ft_strequ(term->command[1], "block"))
		return (BLOCK);
	else if (ft_strequ(term->command[1], "look"))
		return (LOOK);
	else if (ft_strequ(term->command[1], "tp"))
		return (TELEPORT);
	return (INV_COMMAND);
}

int		parse_command_content(t_erm *term, int cmd_num)
{
	if (term->cmd_i != 2 || cmd_num < 2)
		return (INV_COMMAND);
	else if (ft_strequ(term->command[2], "minecraft"))
		return (MINECRAFT);
	else if (ft_strequ(term->command[2], "wolf"))
		return (WOLF3D);
	else if (ft_strequ(term->command[2], "compass"))
		return (COMPASS_MODE);
	else if (ft_strequ(term->command[2], "index"))
		return (INDEX_MODE);
	else if (ft_strequ(term->command[2], "freeze"))
		return (FREEZE);
	else if (ft_strequ(term->command[2], "unfreeze"))
		return (UNFREEZE);
	else if (ft_strequ(term->command[2], "default"))
		return (DEFAULT);
	return (ft_atoi(term->command[2]));
}

int		parse_command_content2(t_erm *term, int cmd_num, int lim)
{
	if (term->cmd_i != lim || cmd_num < lim)
		return (INV_COMMAND);
	return (ft_atoi(term->command[lim]));
}

void	parse_command(t_wolf *wolf, t_erm *term)
{
	int		cmd_num;

	cmd_num = 0;
	while (term->command[cmd_num])
		cmd_num++;
	if (cmd_num < MIN_COMMAND_SIZE)
		return ;
	term->parsed_command[term->cmd_i++] = parse_command_type(term, cmd_num);
	term->parsed_command[term->cmd_i++] = parse_command_target(term, cmd_num);
	term->parsed_command[term->cmd_i++] = parse_command_content(term, cmd_num);
	term->parsed_command[term->cmd_i++] =
			parse_command_content2(term, cmd_num, 3);
	term->parsed_command[term->cmd_i++] =
			parse_command_content2(term, cmd_num, 4);
	process_full_command(wolf, term);
}
