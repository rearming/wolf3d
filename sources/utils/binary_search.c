/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:36:04 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/05 13:19:50 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_bin_search(int *arr, int elem, int len)
{
	int		i;
	int		left;
	int		right;

	if (!arr)
		return (-1);
	if (len < 1)
		return (-1);
	left = 0;
	right = len - 1;
	while (21)
	{
		if (left > right)
			return (-1);
		i = left + (right - left) / 2;
		if (arr[i] < elem)
			left = i + 1;
		if (arr[i] > elem)
			right = i - 1;
		if (arr[i] == elem)
			return (i);
	}
}
