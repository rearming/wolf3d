/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:39:37 by bbear             #+#    #+#             */
/*   Updated: 2019/09/16 15:05:30 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	game_window(t_wolf *wolf)
{
	player_look(wolf);
	draw_minimap(wolf);
	draw_minimap_fov(wolf);
	draw_animated(&wolf->textures.weapon_frame, wolf->tickrate, wolf->sdl,
	wolf->textures.weapons[(int)wolf->player.weapon_type]);
}
