/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 13:38:51 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_actions(t_actions *actions)
{
	actions->down = FALSE;
	actions->up = FALSE;
	actions->left = FALSE;
	actions->right = FALSE;
	actions->arr_right = FALSE;
	actions->arr_left = FALSE;
	actions->lshift = FALSE;
	actions->lshift_was_pressed = FALSE;
	actions->mouse_right = FALSE;
	actions->mouse_left = FALSE;
	actions->space = FALSE;
}

t_erm		term_init(void)
{
	t_erm		term;

	term.prepare = FALSE;
	term.opened = FALSE;
	term.mem_i = 0;
	while (term.mem_i < TERM_MEM_SIZE)
	{
		ft_bzero(term.buffs[term.mem_i], TERM_BUFF_SIZE);
		term.buffs[term.mem_i][0] = ':';
		term.buffs[term.mem_i][1] = ' ';
		term.mem_i++;
	}
	term.mem_i = 0;
	term.cmd_i = 0;
	term.i = 2;
	term.pos = (t_point){200, WIN_HEIGHT - 170, 0, 0};
	term.text_color = LIGHT_GREY;
	term.line_color = LIGHT_GREY;
	term.scale = 0.06;
	term.command = NULL;
	return (term);
}

static void	init_player(t_wolf *wolf, double fov)
{
	if (wolf->map.player_spawn.x == FALSE)
		raise_error(ERR_NO_PLAYER_SPOT);
	wolf->player.x = (int)wolf->map.player_spawn.x;
	wolf->player.y = (int)wolf->map.player_spawn.y;
	wolf->player.fov = fov;
	wolf->player.angle = 0;
	wolf->player.ang_speed = 0.001;
	wolf->player.speed_fwd = 0.1;
	wolf->player.speed_coeff = 1.5;
	wolf->player.speed_side = wolf->player.speed_fwd / wolf->player.speed_coeff;
	wolf->player.fat = 3;
	wolf->player.look_height = 1;
	wolf->player.look_frozen = TRUE;
	wolf->player.look_coeff = 0;
	wolf->player.weapon_type = GUN;
}

void		wolf_init(t_wolf *wolf)
{
	init_player(wolf, DEF_FOV);
	wolf->minimap.fov_scale = 10;
	wolf->minimap.scale.x = 300;
	wolf->minimap.scale.y = 300;
	wolf->minimap.size.x = 30;
	wolf->minimap.size.y = 30;
	wolf->textures.render_mode = INDEX_MODE;
	wolf->textures.texture_type = WOLF3D;
	wolf->tickrate = 0;
	wolf->textures.head_frame = 1;
	wolf->textures.weapon_frame = 0;
	init_actions(&wolf->actions);
	wolf->no_mouse = TRUE;
	wolf->sdl.pixels = 0;
	wolf->sdl.pitch = 0;
	wolf->map.items = find_items(&wolf->map);
	if (!(wolf->map.item_vis = (double*)malloc(sizeof(double) * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
	if (!(wolf->map.ray_dists = (double*)malloc(sizeof(double) * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
	wolf->term = term_init();
}
