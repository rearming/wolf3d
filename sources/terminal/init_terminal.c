/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_input_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:13:57 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/30 13:01:58 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				close_term(t_erm *term)
{
	term->opened = FALSE;
	term->prepare = FALSE;
	term->i = 2;
	term->cmd_i = 0;
	if (ft_strlen(term->buffs[0]) != 2)
	{
		term->mem_i = TERM_MEM_SIZE - 2;
		while (term->mem_i > 0)
		{
			ft_memcpy(term->buffs[term->mem_i], term->buffs[term->mem_i - 1],
					  TERM_BUFF_SIZE);
			term->mem_i--;
		}
	}
	ft_bzero(term->buffs[0], TERM_BUFF_SIZE);
	term->buffs[0][0] = ':';
	term->buffs[0][1] = ' ';
	return (FALSE);
}

void			get_prev_term_buff(t_wolf *wolf, SDL_Keysym key)
{
	if (key.scancode == SDL_SCANCODE_UP && wolf->term.mem_i < TERM_MEM_SIZE - 1)
	{
		if (ft_strlen(wolf->term.buffs[wolf->term.mem_i + 1]) != 2)
			wolf->term.mem_i++;
	}
	if (key.scancode == SDL_SCANCODE_DOWN && wolf->term.mem_i > 0)
	{
		if (ft_strlen(wolf->term.buffs[wolf->term.mem_i - 1]) != 2
			|| wolf->term.mem_i == 1)
				wolf->term.mem_i--;
	}
}

void			get_term_input(t_wolf *wolf, SDL_Keysym key)
{
	const char	*keyname;

	wolf->term.i = ft_strlen(wolf->term.buffs[wolf->term.mem_i]);
	if (key.scancode == SDL_SCANCODE_UP || key.scancode == SDL_SCANCODE_DOWN)
		return (get_prev_term_buff(wolf, key));
	keyname = SDL_GetScancodeName(key.scancode);
	if (ft_strequ(keyname, DELETE) && wolf->term.i > 2)
		wolf->term.buffs[wolf->term.mem_i][wolf->term.i - 1] = 0;
	else if (ft_strequ(keyname, SPACE))
		wolf->term.buffs[wolf->term.mem_i][wolf->term.i] = ' ';
	else if (!ft_strequ(keyname, ";") && !ft_strequ(keyname, DELETE))
		wolf->term.buffs[wolf->term.mem_i][wolf->term.i] = (char)ft_tolower(keyname[0]);
}

int				check_term(t_wolf *wolf, SDL_Keysym key)
{
	if (key.scancode == SDL_SCANCODE_RETURN && wolf->term.opened)
	{
		wolf->term.command = ft_strsplit(&wolf->term.buffs[wolf->term.mem_i][2], ' ');
		if (wolf->term.command)
			parse_command(wolf, &wolf->term);
		return (close_term(&wolf->term));
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
