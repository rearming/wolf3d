/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:37:02 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/23 16:08:13 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_char(char *str, char breaker)
{
	size_t i;

	i = 0;
	while (str[i] != breaker && str[i] != '\0')
		i++;
	return (i);
}
