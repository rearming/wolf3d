/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:26:24 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/01 11:04:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		move_forward(t_wolf *wolf)
{
	t_point		block;

	block.x = (int)(wolf->player.x + wolf->player.speed_side
			* wolf->player.fat * cos(wolf->player.angle));
	block.y = (int)(wolf->player.y + wolf->player.speed_side
			* wolf->player.fat * sin(wolf->player.angle));
	if (cell_is_empty(&wolf->map, block))
	{
		wolf->player.y += wolf->player.speed_fwd
				* sin(wolf->player.angle);
		wolf->player.x += wolf->player.speed_fwd
				* cos(wolf->player.angle);
	}
}

void		move_back(t_wolf *wolf)
{
	t_point		block;

	block.x = (int)(wolf->player.x - wolf->player.speed_side
			* wolf->player.fat * cos(wolf->player.angle));
	block.y = (int)(wolf->player.y - wolf->player.speed_side
			* wolf->player.fat * sin(wolf->player.angle));
	if (cell_is_empty(&wolf->map, block))
	{
		wolf->player.y -= wolf->player.speed_fwd
				* sin(wolf->player.angle);
		wolf->player.x -= wolf->player.speed_fwd
				* cos(wolf->player.angle);
	}
}

void		move_right(t_wolf *wolf)
{
	t_point		block;

	block.x = (int)(wolf->player.x + wolf->player.speed_side
			* wolf->player.fat * cos(wolf->player.angle + M_PI / 2));
	block.y = (int)(wolf->player.y + wolf->player.speed_side
			* wolf->player.fat * sin(wolf->player.angle + M_PI / 2));
	if (cell_is_empty(&wolf->map, block))
	{
		wolf->player.y += wolf->player.speed_side
				* sin(wolf->player.angle + M_PI / 2);
		wolf->player.x += wolf->player.speed_side
				* cos(wolf->player.angle + M_PI / 2);
	}
}

void		move_left(t_wolf *wolf)
{
	t_point		block;

	block.x = (int)(wolf->player.x + wolf->player.speed_side
			* wolf->player.fat * cos(wolf->player.angle - M_PI / 2));
	block.y = (int)(wolf->player.y + wolf->player.speed_side
			* wolf->player.fat * sin(wolf->player.angle - M_PI / 2));
	if (cell_is_empty(&wolf->map, block))
	{
		wolf->player.y += wolf->player.speed_side
				* sin(wolf->player.angle - M_PI / 2);
		wolf->player.x += wolf->player.speed_side
				* cos(wolf->player.angle - M_PI / 2);
	}
}

void		player_run(t_wolf *wolf)
{
	if (wolf->actions.lshift == TRUE
		&& wolf->actions.lshift_was_pressed == FALSE)
	{
		wolf->player.speed_side *= wolf->player.speed_coeff;
		wolf->player.speed_fwd *= wolf->player.speed_coeff;
		wolf->actions.lshift_was_pressed = TRUE;
	}
	if (wolf->actions.lshift == FALSE
		&& wolf->actions.lshift_was_pressed == TRUE)
	{
		wolf->player.speed_side /= wolf->player.speed_coeff;
		wolf->player.speed_fwd /= wolf->player.speed_coeff;
		wolf->actions.lshift_was_pressed = FALSE;
	}
}
