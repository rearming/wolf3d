/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 14:04:51 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/23 16:08:13 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int 		is_border_block(t_map map, t_point block)
{
	if (block.y != 0 && block.x != 0
		&& block.y < map.height - 1 && block.x < map.width - 1)
		return (FALSE);
	return (TRUE);
}
