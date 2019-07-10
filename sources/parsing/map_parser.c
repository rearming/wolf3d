/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:15:10 by rearming          #+#    #+#             */
/*   Updated: 2019/07/10 13:39:37 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		check_valid(char **map) //todo сделать работу с любыми, даже не прямоугольными картами
{
	int 	x;
	int 	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_isdigit(map[y][x]))
					raise_error(ERR_INV_MAP_SYMBOL);
			x++;
		}
		y++;
	}
}

char 	**get_map(char *filename)
{
	int 	fd;
	char 	**map;

	fd = open(filename, O_RDONLY);
	map = fast_gnl(fd);
	check_valid(map); //todo add check line length (or connection)
	return (map);
}