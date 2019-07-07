/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:11:49 by rearming          #+#    #+#             */
/*   Updated: 2019/06/13 08:39:20 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_power(long nbr, int power)
{
	long	base_nbr;

	base_nbr = nbr;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 1)
	{
		nbr *= base_nbr;
		power--;
	}
	return (nbr);
}
