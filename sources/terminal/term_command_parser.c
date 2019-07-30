/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_command_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:17:08 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/30 13:20:02 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		parse_command_type(t_erm *term)
{
	if (term->cmd_i != 0)
		return (INV_COMMAND);
	if (ft_strequ(term->command[0], "render"))
		return (RENDER);
	if (ft_strequ(term->command[0], "set"))
		return (SET);
	return (INV_COMMAND);
}

int		parse_command_target(t_erm *term)
{
	if (term->cmd_i != 1)
		return (INV_COMMAND);
	if (ft_strequ(term->command[1], "all"))
		return (ALL);
	else if (ft_strequ(term->command[1], "block"))
		return (BLOCK);
	return (INV_COMMAND);
}

int		parse_command_content(t_erm *term)
{
	if (term->cmd_i != 2)
		return (INV_COMMAND);
	else if (ft_strequ(term->command[2], "minecraft"))
		return (MINECRAFT);
	else if (ft_strequ(term->command[2], "wolf"))
		return (WOLF3D);
	else if (ft_strequ(term->command[2], "compass"))
		return (COMPASS_MODE);
	else if (ft_strequ(term->command[2], "index"))
		return (INDEX_MODE);
	return (ft_atoi(term->command[2]));
}

void	parse_command(t_wolf *wolf, t_erm *term)
{
	int		error;
	int		i;

	i = 0;
	while (term->command[i])
		i++;
	if (i < 3)
		return ;
	error = INV_COMMAND;
	error += term->parsed_command[term->cmd_i++] = parse_command_type(term);
	error += term->parsed_command[term->cmd_i++] = parse_command_target(term);
	error += term->parsed_command[term->cmd_i++] = parse_command_content(term);
	if (error != INV_COMMAND)
		process_full_command(wolf, term);
}
