/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_even.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:36:06 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/23 16:08:13 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			is_even(int num)
{
	return (num % 2 == 0 ? 1 : 0);
}
