/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rearming <rearming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:21:01 by rearming          #+#    #+#             */
/*   Updated: 2019/07/15 13:36:11 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_digits_base(char *str, int base)
{
	int		i;
	char	test;

	i = 0;
	while (str[i])
	{
		test = ft_toupper(str[i]);
		if ((ft_isdigit(test) && test <= '0' + base)
			|| (test >= 'A' && test <= 'A' + base - 11))
			i++;
		else
			break ;
	}
	return (i);
}
