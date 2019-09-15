/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 08:17:26 by bbear             #+#    #+#             */
/*   Updated: 2019/09/15 15:53:35 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	scaled_draw_new(t_wolf *wolf, t_sprite sprite,
double scale, t_point print_coord)
{
	int		x;
	int		y;
	t_ray	ray;

	scale = scale < 20 ? scale : 20;
	x = 0;
	while (x < scale * sprite.width)
	{
		y = 0;
		ray = raycast(wolf, ((double)(print_coord.x + x) / 22 / 180 * M_PI));
		if (ray.distance > print_coord.z)
		{
			while (y < scale * sprite.height)
			{
				if ((sprite.data[(int)(y / scale)][(int)(x / scale)] >> 24))
					sdl_put_pixel(&(t_point){x + print_coord.x, y
					+ print_coord.y, 0, sprite.data[(int)(y / scale)]
					[(int)(x / scale)]}, &(wolf->sdl));
				y++;
			}
		}
		x++;
	}
}

void	check_walls(t_wolf *wolf)
{
	int		far[wolf->map.items_nbr];
	int		close[wolf->map.items_nbr];
	int		i[3];
	t_ray	ray;
	double	coord[3];
	double	dist;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	ft_bzero(far, wolf->map.items_nbr);
	ft_bzero(close, wolf->map.items_nbr);
	while (i[0] < wolf->map.items_nbr)
	{
		coord[0] = wolf->map.items[i[0]].x + 0.5 - wolf->player.x;
		coord[1] = wolf->map.items[i[0]].y + 0.5 - wolf->player.y;
		coord[2] = atan2(coord[1], coord[0]);
		if (coord[2] < 0)
			coord[2] += M_PI * 2;
		ray = raycast(wolf, coord[2]);
		dist = sqrt(coord[0] * coord[0] + coord[1] * coord[1]);
		if (ray.distance < dist)
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

void	check_condition(t_wolf *wolf, double atan_item, double *cord, int i,
int flag)
{
	double	dist;

	dist = sqrt(cord[0] * cord[0] + cord[1] * cord[1]) * 0.25;
	if (dist < 0.1)
	{
		wolf->map.int_map[wolf->map.items[i].y][wolf->map.items[i].x] = 0;
		wolf->map.items[i].x = 0;
	}
	if (flag)
		scaled_draw_new(wolf, *wolf->textures.weapons[WEAPONS_NUM - 1].sprite,
					0.5 / dist, (t_point) {(atan_item - wolf->player.angle
					+ wolf->player.fov * 0.5) * 180 / M_PI * 22
					- (*wolf->textures.weapons[WEAPONS_NUM - 1].sprite).width
					* 0.75 / dist * 0.5, WIN_HEIGHT * 0.55 - dist * 10, dist
					* 4, 0});
	else
		scaled_draw(wolf->sdl, *wolf->textures.weapons[WEAPONS_NUM - 1].sprite,
		0.5 / dist, (t_point){(atan_item - wolf->player.angle + wolf->player.fov
		* 0.5) * 180 / M_PI * 22 -
		(*wolf->textures.weapons[WEAPONS_NUM - 1].sprite).width * 0.75 / dist
		* 0.5, WIN_HEIGHT * 0.55 - dist * 10, 0, 0});
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
	if (atan_item < 0)
		atan_item += 2 * M_PI;
	while (wolf->player.angle - wolf->player.fov < 0)
		wolf->player.angle += M_PI * 2;
	while (wolf->player.angle >= M_PI * 2)
		wolf->player.angle -= M_PI * 2;
	if (atan_item <= wolf->player.angle + wolf->player.fov / 2 &&
		atan_item >= wolf->player.angle - wolf->player.fov / 2)
		check_condition(wolf, atan_item, cord, i, flag);
	else if (wolf->player.angle + wolf->player.fov * 0.5 > M_PI * 2)
	{
		wolf->player.angle -= 2 * M_PI;
		if (atan_item >= wolf->player.angle - wolf->player.fov * 0.5 &&
			atan_item <= wolf->player.angle + wolf->player.fov * 0.5)
			check_condition(wolf, atan_item, cord, i, flag);
	}
	else if (atan_item + wolf->player.fov * 0.5 > 2 * M_PI)
	{
		atan_item -= 2 * M_PI;
		if (atan_item >= wolf->player.angle - wolf->player.fov * 0.5 &&
			atan_item <= wolf->player.angle + wolf->player.fov * 0.5)
			check_condition(wolf, atan_item, cord, i, flag);
	}
}
