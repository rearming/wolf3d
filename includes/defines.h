/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:24:54 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/09 14:25:24 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "wolf3d.h"

# ifdef __APPLE__
#  define WIN_WIDTH 630 //2550 //630
#  define WIN_HEIGHT 320 //1300 //320
# else
#  define WIN_WIDTH 1200
#  define WIN_HEIGHT 800
# endif

# define TRUE 1
# define FALSE 0

# define BUFF_SIZE 2000000

# define PLAYER_POS 53

# define BMP_IMG 100
# define STB_IMG 101

# define SVA_EAGLE 102
# define HITLER 103

#endif
