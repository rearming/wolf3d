/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:33:44 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 20:05:36 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		mouse_hook(t_wolf *wolf, SDL_Event event)
{
	wolf->player.angle += (double)event.motion.xrel / 1000;
}