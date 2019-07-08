/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:06:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 16:15:32 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 		map_raycast(t_wolf *wolf, double angle)
{
	double 		x;
	double 		y;
	int 		fov;
	double 		distance;
	t_point		scale;

	scale.x = 7;
	scale.y = 14;
	angle = wolf->player.angle - wolf->player.fov / 2;
	fov = 180 / M_PI * wolf->player.fov;
	while (fov)
	{
		distance = 0;
		while (distance < 50)
		{
			x = wolf->player.x + distance * cos(angle);
			y = wolf->player.y + distance * sin(angle);
			distance += 0.05;
			sdl_put_pixel(wolf, (t_point){x * scale.x, y * scale.y, 0, M_TURQOISE});
			if (wolf->map[(int) y][(int) x] != '0')
				break;
		}
		angle += wolf->player.fov / 60;
		fov--;
	}
}

void		draw_player(t_wolf *wolf)
{
	t_point		player_pos;
	t_point		scale;

	scale.y = 14;
	scale.x = 7;
	player_pos.x = wolf->player.x * scale.x;
	player_pos.y = wolf->player.y * scale.y;
	player_pos.color = BLACK;
	sdl_put_pixel(wolf, player_pos);
	map_raycast(wolf, wolf->player.angle);
}

void		draw_minimap(t_wolf *wolf)
{
	t_point		m_size;
	int 		x;
	int 		y;
	t_point		scale;

	scale.y = 14;
	scale.x = 7;
	m_size.x = ft_strlen(wolf->map[0]);
	m_size.y = 0;
	while (wolf->map[m_size.y])
		m_size.y++;
	y = 0;
	while (y < m_size.y * scale.y)
	{
		x = 0;
		while (x < m_size.x * scale.x)
		{
			if (wolf->map[y / scale.y][x / scale.x] == '0')
				sdl_put_pixel(wolf, (t_point) {x, y, 0, GREY});
			else
				sdl_put_pixel(wolf,
						(t_point){x, y, 0,
				get_wall_color(x / scale.x, y / scale.y, wolf->map)});
			x++;
		}
		y++;
	}
	draw_player(wolf);
}