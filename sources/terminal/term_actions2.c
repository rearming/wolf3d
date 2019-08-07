/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_actions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:39:01 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/07 16:13:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		teleport_player(t_wolf *wolf, t_erm *term)
{
	t_point		tp_point;

	tp_point.x = term->parsed_command[2];
	tp_point.y = term->parsed_command[3];
	if (!is_border_block(&wolf->map, tp_point)
	&& cell_is_empty(&wolf->map, tp_point))
	{
		wolf->player.x = tp_point.x;
		wolf->player.y = tp_point.y;
	}
}

static int	get_channel(char channel)
{
	if (channel == 'r')
		return (0);
	if (channel == 'g')
		return (1);
	return (2);
}

void		change_channels(t_wolf *wolf, t_erm *term)
{
	int		channel;

	channel = 0;
	if (term->parsed_command[2] == DEFAULT)
	{
		wolf->textures.channels[0] = 0;
		wolf->textures.channels[1] = 1;
		wolf->textures.channels[2] = 2;
		return ;
	}
	if (ft_strlen(term->command[2]) != 3)
		return ;
	while (channel < 3)
	{
		wolf->textures.channels[channel] =
				get_channel(term->command[2][channel]);
		channel++;
	}
}
