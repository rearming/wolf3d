/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:38 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/25 16:59:45 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		init_sdl(void)
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(sdl.win = SDL_CreateWindow("Dota 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		raise_error(ERR_SDL_WIN);
	if (!(sdl.rend = SDL_CreateRenderer(sdl.win, -1, SDL_RENDERER_SOFTWARE)))
		raise_error(ERR_SDL_RENDER);
	if (!(sdl.texture = SDL_CreateTexture(sdl.rend, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
	return (sdl);
}

t_ttf		init_ttf(char *font_file)
{
	t_ttf	ttf;
	int		ret;

	ttf.font = NULL;
	ret = TTF_Init();
	if (ret == TTF_ERROR)
		raise_error(ERR_SDL_TTF_INIT);
	if (!(ttf.font = TTF_OpenFont(font_file, 150)))
		raise_error(ERR_SDL_TTF_OPENFONT);
	return (ttf);
}

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
}

t_erm 		term_init(void)
{
	t_erm		term;

	term.prepare = FALSE;
	term.opened = FALSE;
	term.cmd_i = 0;
	while (term.cmd_i < TERM_MEM_SIZE)
	{
		ft_bzero(term.prev_cmd[term.cmd_i], TERM_CMD_SIZE);
		term.cmd_i++;
	}
	ft_bzero(term.buff, TERM_CMD_SIZE);
	term.buff[0] = ':';
	term.buff[1] = ' ';
	term.cmd_i = 0;
	term.i = 2;
	term.pos = (t_point){200, WIN_HEIGHT - 200};
	term.text_color = LIGHT_GREY;
	term.line_color = LIGHT_GREY;
	term.scale = 0.3;
	return (term);
}

void		wolf_init(t_wolf *wolf)
{
	if (wolf->map.player_spawn.x == FALSE)
		raise_error(ERR_NO_PLAYER_SPOT);
	wolf->player.x = (int)wolf->map.player_spawn.x;
	wolf->player.y = (int)wolf->map.player_spawn.y;
	wolf->player.fov = M_PI / 2; // pi / 3 = 60 градусов, pi / 2 = 90
	wolf->player.angle = 0;
	wolf->player.ang_speed = 0.001;
	wolf->player.speed_fwd = 0.3;
	wolf->player.speed_side = 0.15;
	wolf->player.fat = 3;

	wolf->minimap.fov_scale = 10;
	wolf->minimap.scale.x = 300;
	wolf->minimap.scale.y = 300;
	wolf->minimap.size.x = 30;
	wolf->minimap.size.y = 30;

	//todo get this info from args
	//wolf->textures.render_mode = COMPASS_MODE;
	wolf->textures.render_mode = NUMBER_MODE;
	//wolf->textures.texture_mode = MINECRAFT;
	wolf->textures.texture_mode = WOLF3D;

	wolf->textures.frame = 1;
	wolf->textures.w_frame = 0;
	wolf->player.weapon_type = GUN;
	init_actions(&wolf->actions);
	wolf->no_mouse = TRUE;
	if (!(wolf->sdl.pixels = (int*)malloc(sizeof(int)
			* WIN_HEIGHT * WIN_WIDTH)))
		raise_error(ERR_MALLOC);
	wolf->map.items = find_items(wolf);
	wolf->term = term_init();
}
