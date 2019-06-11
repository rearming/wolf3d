/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:24:54 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/03 16:20:04 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "wolf3d.h"

# ifdef __APPLE__
#  define WIN_WIDTH 2550
#  define WIN_HEIGHT 1300
# else
#  define WIN_WIDTH 1820
#  define WIN_HEIGHT 980
# endif

# define TRUE 1
# define FALSE 0

#endif
