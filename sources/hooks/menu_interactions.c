/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:47:49 by bbear             #+#    #+#             */
/*   Updated: 2019/09/15 15:41:41 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	interactions(t_wolf *wolf, int width, int height)
{
	if (wolf->mouse_y <= height * 2 && wolf->mouse_y >= height)
		if (wolf->mouse_x >= width && wolf->mouse_x <= width * 3)
			if (wolf->actions.mouse_left && wolf->flag == 1)
				wolf->flag = 0;
	if (wolf->mouse_y <= height * 6 && wolf->mouse_y >= height * 5)
		if (wolf->mouse_x >= width && wolf->mouse_x <= width * 3)
			if (wolf->actions.mouse_left && wolf->flag == 1)
				sdl_exit(wolf);
	if (wolf->mouse_y <= height * 4 && wolf->mouse_y >= height * 3)
		if (wolf->mouse_x >= width && wolf->mouse_x <= width * 3)
			if (wolf->actions.mouse_left && wolf->flag == 1)
				wolf->flag = 2;
	if (wolf->mouse_y <= height && wolf->mouse_y >= height * 0.5)
		if (wolf->mouse_x >= width * 0.25 &&
			wolf->mouse_x <= width - 100 * SCALE_WIDTH)
			if (wolf->actions.mouse_left && (wolf->flag == 2 ||
			wolf->flag == 3))
				wolf->flag = 1;
	if (wolf->mouse_y <= height * 7 && wolf->mouse_y >= height * 6)
		if (wolf->mouse_x >= width && wolf->mouse_x <= width * 3)
			if (wolf->actions.mouse_left && wolf->flag == 1)
				wolf->flag = 3;
}

void	maps_interactions(t_wolf *wolf, int width, int height)
{
	if (wolf->mouse_y >= height * 2 && wolf->mouse_y <= height * 3)
		if (wolf->mouse_x >= width && wolf->mouse_x <= width * 2)
			if (wolf->actions.mouse_left && wolf->flag == 3)
				choose_map(wolf, 1);
	if (wolf->mouse_y >= height * 2 && wolf->mouse_y <= height * 3)
		if (wolf->mouse_x >= width * 3 && wolf->mouse_x <= width * 4)
			if (wolf->actions.mouse_left && wolf->flag == 3)
				choose_map(wolf, 2);
	if (wolf->mouse_y >= height * 2 && wolf->mouse_y <= height * 3)
		if (wolf->mouse_x >= width * 5 && wolf->mouse_x <= width * 6)
			if (wolf->actions.mouse_left && wolf->flag == 3)
				choose_map(wolf, 3);
	if (wolf->mouse_y >= height * 4 && wolf->mouse_y <= height * 5)
		if (wolf->mouse_x >= width && wolf->mouse_x <= width * 2)
			if (wolf->actions.mouse_left && wolf->flag == 3)
				choose_map(wolf, 4);
	if (wolf->mouse_y >= height * 4 && wolf->mouse_y <= height * 5)
		if (wolf->mouse_x >= width * 3 && wolf->mouse_x <= width * 4)
			if (wolf->actions.mouse_left && wolf->flag == 3)
				choose_map(wolf, 5);
	if (wolf->mouse_y >= height * 4 && wolf->mouse_y <= height * 5)
		if (wolf->mouse_x >= width * 5 && wolf->mouse_x <= width * 6)
			if (wolf->actions.mouse_left && wolf->flag == 3)
				choose_map(wolf, 6);
}

void	mouse_cords(t_wolf *wolf)
{
	int height;
	int width;

	height = (WIN_HEIGHT * SCALE_HEIGHT) / 7;
	width = (WIN_WIDTH * SCALE_WIDTH) / 4;
	interactions(wolf, width, height);
	height = (WIN_HEIGHT * SCALE_HEIGHT) / 6;
	width = (WIN_WIDTH * SCALE_WIDTH) / 7;
	maps_interactions(wolf, width, height);
}
