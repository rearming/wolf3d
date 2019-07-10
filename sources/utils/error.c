/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:16:36 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 08:12:38 by rearming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 		raise_error(int err_code)
{
	if (err_code == ERR_INV_ARGS)
		ft_printf("Expected one arg!");
	exit(err_code);
}