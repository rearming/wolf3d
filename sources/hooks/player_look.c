/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_look.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 11:53:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/01 16:35:42 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		player_look_down(t_wolf *wolf)
{
	int		y;
	int		x;

	y = 0;
	while (y < WIN_HEIGHT - 1 + wolf->player.look_height)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			wolf->sdl.pixels[x + y * WIN_WIDTH] =
					wolf->sdl.pixels[x + (y - wolf->player.look_height)
					* WIN_WIDTH];
			wolf->sdl.pixels
			[x + (y - wolf->player.look_height) * WIN_WIDTH] = FLOOR_GREY;
			x++;
		}
		y++;
	}
}

void		player_look_up(t_wolf *wolf)
{
	int		y;
	int		x;

	y = WIN_HEIGHT - 1;
	while (y > wolf->player.look_height)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			wolf->sdl.pixels[x + y * WIN_WIDTH] =
					wolf->sdl.pixels[x + (y - wolf->player.look_height)
					* WIN_WIDTH];
			wolf->sdl.pixels
			[x + (y - wolf->player.look_height) * WIN_WIDTH] = BLACK;
			x++;
		}
		y--;
	}
}

void		player_look(t_wolf *wolf)
{
	if (wolf->player.look_frozen)
		return ;
	wolf->player.look_height -= wolf->player.look_coeff;
	if (wolf->player.look_height > LOOK_LIMIT
	|| wolf->player.look_height < -LOOK_LIMIT)
		wolf->player.look_height += wolf->player.look_coeff;
	if (wolf->player.look_height > 0)
		player_look_up(wolf);
	else
		player_look_down(wolf);
	wolf->player.look_coeff = 0;
}
