/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_input_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:13:57 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/26 16:10:29 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				close_term(t_wolf *wolf)
{
	wolf->term.opened = FALSE;
	wolf->term.prepare = FALSE;
	ft_bzero(&wolf->term.buff[2], TERM_BUFF_SIZE - 2);
	wolf->term.i = 2;
	wolf->term.cmd_i = 0;
	return (FALSE);
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
}

int				check_term(t_wolf *wolf, SDL_Keysym key)
{
	if (key.scancode == SDL_SCANCODE_RETURN && wolf->term.opened)
	{
		printf("terminal's buf: [%s]\n", wolf->term.buff);
		wolf->term.command = ft_strsplit(&wolf->term.buff[1], ' ');
		if (wolf->term.command)
			parse_command(wolf, &wolf->term);
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
