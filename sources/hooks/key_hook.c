/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:29:22 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/25 17:01:41 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			keyup_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_UP
		|| event.key.keysym.scancode == SDL_SCANCODE_W)
		wolf->actions.up = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event.key.keysym.scancode == SDL_SCANCODE_S)
		wolf->actions.down = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT
		|| event.key.keysym.scancode == SDL_SCANCODE_D)
		wolf->actions.right = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT
		|| event.key.keysym.scancode == SDL_SCANCODE_A)
		wolf->actions.left = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->actions.lshift = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		wolf->actions.arr_right = FALSE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		wolf->actions.arr_left = FALSE;
}

void			process_command(t_wolf *wolf)
{

}

void			get_term_input(t_wolf *wolf, SDL_Keysym key)
{
	const char	*keyname;

	keyname = SDL_GetScancodeName(key.scancode);
	if (ft_strequ(keyname, DELETE))
	{
		if (wolf->term.i > 2)
		{
			wolf->term.buff[wolf->term.i - 1] = 0;
			wolf->term.i--;
		}
	}
	else if (ft_strequ(keyname, SPACE))
	{
		wolf->term.buff[wolf->term.i] = ' ';
		wolf->term.i++;
	}
	else if (!ft_strequ(keyname, ";"))
	{
		wolf->term.buff[wolf->term.i] = (char)ft_tolower(keyname[0]);
		wolf->term.i++;
	}
	printf("terminal's buf: [%s]\n", wolf->term.buff);
}

int				close_term(t_wolf *wolf)
{
	wolf->term.opened = FALSE;
	wolf->term.prepare = FALSE;
	ft_bzero(&wolf->term.buff[2], TERM_CMD_SIZE - 2);
	wolf->term.i = 2;
	return (FALSE);
}

int				check_term(t_wolf *wolf, SDL_Keysym key)
{
	if (key.scancode == SDL_SCANCODE_RETURN && wolf->term.opened)
	{
		process_command(wolf);
		return (close_term(wolf));
	}
	if (key.scancode == SDL_SCANCODE_LCTRL && !wolf->term.prepare)
	{
		wolf->term.prepare = TRUE;
		return (FALSE);
	}
	if ((key.sym == SDLK_COLON || key.sym == SDLK_SEMICOLON) && wolf->term.prepare)
	{
		wolf->term.opened = TRUE;
		return (TRUE);
	}
	if (wolf->term.opened)
		return (TRUE);
	return (FALSE);
}

void			keydown_hook(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		sdl_exit(wolf);
	if (check_term(wolf, event.key.keysym))
		return (get_term_input(wolf, event.key.keysym));
	if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		wolf->actions.arr_right = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		wolf->actions.arr_left = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_UP
		|| event.key.keysym.scancode == SDL_SCANCODE_W)
		wolf->actions.up = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN
		|| event.key.keysym.scancode == SDL_SCANCODE_S)
		wolf->actions.down = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_D)
		wolf->actions.right = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_A)
		wolf->actions.left = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		wolf->actions.lshift = TRUE;
	if (event.key.keysym.scancode == SDL_SCANCODE_P)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (event.key.keysym.scancode == SDL_SCANCODE_R)
		SDL_SetRelativeMouseMode(SDL_TRUE);
}
