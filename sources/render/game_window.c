/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:39:37 by bbear             #+#    #+#             */
/*   Updated: 2019/09/27 18:42:49 by bbear            ###   ########.fr       */
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

void	clean_map(t_wolf *wolf)
{
	int		y;

	free(wolf->map.item_vis);
	wolf->map.item_vis = NULL;
	free(wolf->map.ray_dists);
	wolf->map.ray_dists = NULL;
	free(wolf->map.items);
	wolf->map.items = NULL;
	y = -1;
	while (++y < wolf->map.height)
		free(wolf->map.int_map[y]);
	free(wolf->map.int_map);
	wolf->map.int_map = NULL;
	y = -1;
	while (++y < wolf->map.height)
		free(wolf->map.backup[y]);
	free(wolf->map.backup);
	wolf->map.backup = NULL;
}
