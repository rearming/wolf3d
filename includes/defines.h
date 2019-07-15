/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:24:54 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/15 19:47:02 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "wolf3d.h"

# ifdef __APPLE__
#  define WIN_WIDTH 1980
#  define WIN_HEIGHT 1020

//#  define WIN_WIDTH 2550
//#  define WIN_HEIGHT 1300

# else
#  define WIN_WIDTH 1980
#  define WIN_HEIGHT 1020
# endif

# define TRUE 1
# define FALSE 0

# define PLAYER_POS 53

# define BMP_IMG 100
# define STB_IMG 101

# define SVA_FLAG 102
# define ROCK_WALL 103
# define HITLER 104
# define RED_BRICKS 105
# define SVA_EAGLE 106

# define VIEW_UP 501
# define VIEW_DOWN 502
# define VIEW_RIGHT 503
# define VIEW_LEFT 504

# define NUMBER_MODE 665
# define COMPASS_MODE 666

# define MAX_MAP_SIZE 10000

# define MOVING 667
# define IDLE 668

# define GUN 1001
# define KNIFE 1002
# define DAKKA 1003

#endif
