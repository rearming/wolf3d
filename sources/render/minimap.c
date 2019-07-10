/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:06:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 13:56:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		map_raycast(t_wolf *wolf)
{
	t_ray		ray;
	double 		angle;
	int 		fov;

	angle = wolf->player.angle - wolf->player.fov / 2;
	fov = 180 / M_PI * wolf->player.fov;
	while (fov)
	{
		ray.distance = 0;
		while (ray.distance < 50)
		{
			ray.x = wolf->player.x + ray.distance * cos(angle);
			ray.y = wolf->player.y + ray.distance * sin(angle);
			ray.distance += 0.05;
			sdl_put_pixel((t_point)
								  {ray.x * wolf->minimap.scale.x,
								   ray.y * wolf->minimap.scale.y, 0,
								   M_TURQOISE}, wolf->sdl);
			if (!cell_is_empty(wolf->map[(int)ray.y][(int)ray.x]))
				break;
		}
		angle += wolf->player.fov / 60;
		fov--;
	}
}

void		draw_player(t_wolf *wolf)
{
	t_point		player_pos;

	player_pos.x = wolf->player.x * wolf->minimap.scale.x;
	player_pos.y = wolf->player.y * wolf->minimap.scale.y;
	player_pos.color = BLACK;
	sdl_put_pixel(player_pos, wolf->sdl);
	map_raycast(wolf);
}

void		draw_minimap(t_wolf *wolf)
{
	t_point		m_size;
	int 		x;
	int 		y;

	m_size.x = ft_strlen(wolf->map[0]);
	m_size.y = 0;
	while (wolf->map[m_size.y])
		m_size.y++;
	y = 0;
	while (y < m_size.y * wolf->minimap.scale.y)
	{
		x = 0;
		while (x < m_size.x * wolf->minimap.scale.x)
		{
			if (cell_is_empty(wolf->map[y / wolf->minimap.scale.y][x / wolf->minimap.scale.x]))
				sdl_put_pixel((t_point) {x, y, 0, GREY}, wolf->sdl);
			else
				sdl_put_pixel((t_point)
									  {x, y, 0, get_texture_type(
											  x / wolf->minimap.scale.x,
											  y / wolf->minimap.scale.y,
											  wolf->map)}, wolf->sdl);
			x++;
		}
		y++;
	}
	draw_player(wolf);
}