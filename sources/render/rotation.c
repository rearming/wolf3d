/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:59:08 by sleonard          #+#    #+#             */
/*   Updated: 2019/05/13 11:19:47 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		rotate_y(t_point *point, double angle)
{
	t_point		temp;

	temp = *point;
	point->x = (int)(point->x * cos(angle) + point->z * sin(angle));
	point->z = (int)(-temp.x * sin(angle) + point->z * cos(angle));
}

void		rotate_x(t_point *point, double angle)
{
	t_point		temp;

	temp = *point;
	point->y = (int)(point->y * cos(angle) + point->z * sin(angle));
	point->z = (int)(-temp.y * sin(angle) + point->z * cos(angle));
}

void		rotate_z(t_point *point, double angle)
{
	t_point		temp;

	temp = *point;
	point->x = (int)(point->x * cos(angle) - point->y * sin(angle));
	point->y = (int)(temp.x * sin(angle) + point->y * cos(angle));
}
