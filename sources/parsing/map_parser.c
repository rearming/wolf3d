/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:15:10 by rearming          #+#    #+#             */
/*   Updated: 2019/07/07 23:30:49 by rearming         ###   ########.fr       */
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

void	free_list(t_list **list)
{
	t_list	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp);
	}
}

char 	**get_map(char *filename)
{
	int 	fd;
	int 	lines;
	char 	*line;
	char 	**map;
	t_list	*list;
	t_list	*lst_begin;
	int 	line_width;
	int 	valid_width;

	lines = 0;
	valid_width = -3;
	fd = open(filename, O_RDONLY);
	list = NULL;
	line = NULL;
	while ((line_width = get_next_line(fd, &line)))
	{
		if (line_width == -1)
			raise_error(ERR_INV_FILE);
		if (valid_width == -3)
			valid_width = line_width;
		if (valid_width != line_width)
			raise_error(ERR_INV_MAP);
		ft_lstaddback(&list, line, ft_strlen(line));
		lines++;
		free(line);
	}
	map = (char**)malloc(sizeof(char*) * lines);
	map[lines] = 0;
	lines = 0;
	lst_begin = list;
	while (42)
	{
		map[lines] = list->content;
		list = list->next;
		lines++;
		if (!list)
			break ;
	}
	free_list(&lst_begin);
	check_valid(map);
	return (map);
}