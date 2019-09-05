/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:47:49 by bbear             #+#    #+#             */
/*   Updated: 2019/09/05 20:27:33 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    mouse_cords(t_wolf *wolf)//, SDL_Event *event)
{
    int         height;
    int         width;
    int         x;
    int         y;

    height = (WIN_HEIGHT * SCALE_HEIGHT) / 7;
    width = (WIN_WIDTH * SCALE_WIDTH) / 4;
    x = wolf->mouse_x;
    y = wolf->mouse_y;
    if (y <= height * 2 && y >= height)
        if (x >= width && x <= width * 3)
            if (wolf->actions.mouse_left == TRUE)
            {
                wolf->flag = 0;
                printf("x position: %d \n", x);
                printf("y position: %d \n", y);
                printf("height: %d \n", height);
                printf("width: %d \n\n", width);
            }

    if (y <= height * 6 && y >= height * 5)
        if (x >= width && x <= width * 3)
            if (wolf->actions.mouse_left == TRUE)
                sdl_exit(wolf);
}