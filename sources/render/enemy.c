/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbear <bbear@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 23:29:02 by bbear             #+#    #+#             */
/*   Updated: 2019/08/27 01:45:24 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    en_move(t_wolf *wolf)
{
    if (!wolf->map.items[1].x)
        return ;
//    if (!wolf->map.int_map[wolf->map.items[1].y][(int)(wolf->map.items[1].x + 1)])
//    {
//		wolf->mulx += 1;
//        if (wolf->mulx == 10)
//		{
//			wolf->map.items[1].x += 1;
//        	wolf->map.int_map[wolf->map.items[1].y][wolf->map.items[1].x] = wolf->map.int_map[wolf->map.items[1].y][wolf->map.items[1].x - 1];
//        	wolf->map.int_map[wolf->map.items[1].y][wolf->map.items[1].x - 1] = 0;
//			wolf->mulx = 0;
//		}
//    }

//    else if (wolf->map.int_map[(int)(wolf->map.items[0].y + 0.1)][wolf->map.items[0].x] < 1)
//        wolf->map.items[0].y += 1;
}
//допилить надо бы, а то не работает
//ну или работает, но very very bad
