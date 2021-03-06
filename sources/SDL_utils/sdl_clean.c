/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:15:28 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/01 11:04:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sdl_clean(t_wolf *wolf)
{
	SDL_DestroyRenderer(wolf->sdl.rend);
	SDL_DestroyWindow(wolf->sdl.win);
	SDL_Quit();
}
