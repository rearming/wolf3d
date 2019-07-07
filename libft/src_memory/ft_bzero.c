/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:50:23 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/13 08:39:20 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_bzero(void *dest, size_t n)
{
	unsigned char	*arr;
	size_t			i;

	i = 0;
	arr = dest;
	if (n == 0)
		return (dest);
	while (i < n)
	{
		arr[i] = 0;
		i++;
	}
	return (dest);
}
