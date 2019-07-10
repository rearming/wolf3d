/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:06:46 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 15:08:19 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sdl_loop(t_wolf *wolf)
{
	SDL_Event		event;


	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
				key_hook(wolf, event);
			if (event.type == SDL_MOUSEMOTION)
			{
				mouse_hook(wolf, event);
			}
		}
		if (event.type == SDL_QUIT)
			break ;
		//int 	curr_time = SDL_GetTicks();
		render(wolf);
		//ft_printf("Rendered in [%i] milliseconds\n", SDL_GetTicks() - curr_time);
	}
}
