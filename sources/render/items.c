/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 08:17:26 by bbear             #+#    #+#             */
/*   Updated: 2019/09/27 22:48:47 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check_walls(t_wolf *wolf)
{
	int		far[wolf->map.items_nbr];
	int		close[wolf->map.items_nbr];
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	ft_bzero(far, wolf->map.items_nbr);
	ft_bzero(close, wolf->map.items_nbr);
	while (i[0] < wolf->map.items_nbr)
	{
		if (check_walls_utils(wolf, i[0]))
		{
			far[i[1]] = i[0] + 1;
			i[1]++;
		}
		else
		{
			close[i[2]] = i[0] + 1;
			i[2]++;
		}
		i[0]++;
	}
	draw_items(wolf, far, close);
}

void	draw_items(t_wolf *wolf, int *far, int *close)
{
	int		i;
	int		j;

	i = 0;
	while (far[i] <= wolf->map.items_nbr && far[i] > 0)
	{
		draw_item(wolf, far[i] - 1, 1);
		i++;
	}
	render_columns(wolf);
	j = 0;
	while (close[j] <= wolf->map.items_nbr && close[j] > 0
	&& j < wolf->map.items_nbr - i)
	{
		draw_item(wolf, close[j] - 1, 0);
		j++;
	}
}

void	check_condition(t_wolf *wolf, double atan_item, int i, int flag)
{
	double	dist;

	dist = wolf->dist;
	if (dist < 0.1)
	{
		wolf->map.int_map[wolf->map.items[i].y][wolf->map.items[i].x] = 0;
		wolf->map.items[i].x = 0;
	}
	if (flag)
		scaled_draw_new(wolf, *wolf->textures.weapons[WEAPONS_NUM - 1].sprite,
		0.5 / dist, (t_point) {(atan_item - wolf->player.angle
		+ wolf->player.fov * 0.5) * 180 / M_PI * 32
		- (*wolf->textures.weapons[WEAPONS_NUM - 1].sprite).width
		* 0.75 / dist * 0.5, WIN_HEIGHT * 0.55 - dist * 10, dist
		* 4, 0});
	else
		scaled_draw(wolf->sdl, *wolf->textures.weapons[WEAPONS_NUM - 1].sprite,
		0.5 / dist, (t_point){(atan_item - wolf->player.angle + wolf->player.fov
		* 0.5) * 180 / M_PI * 32 -
		(*wolf->textures.weapons[WEAPONS_NUM - 1].sprite).width * 0.75 / dist
		* 0.5, WIN_HEIGHT * 0.55 - dist * 10, 0, 0});
}

void	check_draw(t_wolf *wolf, int i, int flag, double atan_item)
{
	if (atan_item <= wolf->player.angle + wolf->player.fov / 2 &&
		atan_item >= wolf->player.angle - wolf->player.fov / 2)
		check_condition(wolf, atan_item, i, flag);
	else if (wolf->player.angle + wolf->player.fov * 0.5 > M_PI * 2)
	{
		wolf->player.angle -= 2 * M_PI;
		if (atan_item >= wolf->player.angle - wolf->player.fov * 0.5 &&
			atan_item <= wolf->player.angle + wolf->player.fov * 0.5)
			check_condition(wolf, atan_item, i, flag);
	}
	else if (atan_item + wolf->player.fov * 0.5 > 2 * M_PI)
	{
		atan_item -= 2 * M_PI;
		if (atan_item >= wolf->player.angle - wolf->player.fov * 0.5 &&
			atan_item <= wolf->player.angle + wolf->player.fov * 0.5)
			check_condition(wolf, atan_item, i, flag);
	}
}

void	draw_item(t_wolf *wolf, int i, int flag)
{
	double	cord[2];
	double	atan_item;

	if (wolf->map.items[i].x == 0)
		return ;
	cord[0] = wolf->map.items[i].x + 0.5 - wolf->player.x;
	cord[1] = wolf->map.items[i].y + 0.5 - wolf->player.y;
	atan_item = atan2(cord[1], cord[0]);
	wolf->dist = sqrt(cord[0] * cord[0] + cord[1] * cord[1]) * 0.25;
	if (atan_item < 0)
		atan_item += 2 * M_PI;
	while (wolf->player.angle - wolf->player.fov < 0)
		wolf->player.angle += M_PI * 2;
	while (wolf->player.angle >= M_PI * 2)
		wolf->player.angle -= M_PI * 2;
	check_draw(wolf, i, flag, atan_item);
}
