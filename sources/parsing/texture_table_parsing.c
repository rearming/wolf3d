/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_table_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:45:26 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 14:18:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	**init_table(const char *config, int *i, int *tab_i, int **table)
{
	char	**raw_table;

	raw_table = 0;
	if (!ft_strequ(config, "../wolf_ignore.wolf"))
		raise_error(ERR_INV_TEXTURE_TABLE);
	if (!(table[0] = (int*)malloc(sizeof(int) * WOLF_SPRITES)))
		raise_error(ERR_MALLOC);
	if (!(table[1] = (int*)malloc(sizeof(int) * MINE_SPRITES)))
		raise_error(ERR_MALLOC);
	ft_bzero(table[0], sizeof(int) * WOLF_SPRITES);
	ft_bzero(table[1], sizeof(int) * MINE_SPRITES);
	if (!(raw_table = fast_gnl(open(config, O_RDONLY))))
		raise_error(ERR_INV_TEXTURE_TABLE);
	if (!ft_strequ(raw_table[0], "wolf ignore:"))
		raise_error(ERR_INV_TEXTURE_TABLE);
	*i = 1;
	*tab_i = 0;
	return (raw_table);
}

void		ft_bubble_sort(int *arr, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < (size - i - 1))
		{
			if (arr[j] > arr[j + 1])
				ft_swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

static int	check_string(char **raw_table, int *i, int *tab_i, int file_i)
{
	if (!ft_isdigit(raw_table[file_i][0]) &&
		!ft_strequ(raw_table[file_i], "minecraft ignore:"))
		raise_error(ERR_INV_TEXTURE_TABLE);
	else if (ft_strequ(raw_table[file_i], "minecraft ignore:"))
	{
		*i = 0;
		*tab_i = 1;
	}
	if ((file_i >= WOLF_SPRITES && *tab_i == WOLF3D)
		|| (file_i >= MINE_SPRITES && *tab_i == MINECRAFT))
		return (0);
	return (1);
}

int			**get_texture_table(const char *config)
{
	int		**table;
	char	**raw_table;
	int		i;
	int		file_i;
	int		tab_i;

	if (!(table = (int**)malloc(sizeof(int*) * TILEMAPS)))
		raise_error(ERR_MALLOC);
	raw_table = init_table(config, &i, &tab_i, table);
	file_i = 1;
	while (raw_table[file_i])
	{
		if (!(check_string(raw_table, &i, &tab_i, file_i)))
			break ;
		table[tab_i][i] = ft_atoi(raw_table[file_i]);
		i++;
		file_i++;
	}
	ft_bubble_sort(table[0], WOLF_SPRITES);
	ft_bubble_sort(table[1], MINE_SPRITES);
	clean_chr_mtrx(raw_table);
	return (table);
}
