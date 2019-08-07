/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:24:54 by sleonard          #+#    #+#             */
/*   Updated: 2019/08/07 13:35:28 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifdef __APPLE__

#  define WIN_WIDTH 1920
#  define WIN_HEIGHT 1080

#  define SCALE_WIDTH 1.328
#  define SCALE_HEIGHT 1.274

# else
#  define WIN_WIDTH 1980
#  define WIN_HEIGHT 1020

#  define SCALE_WIDTH 1
#  define SCALE_HEIGHT 1

# endif

# define TRUE 1
# define FALSE 0

# define SEARCH_FAIL -1

# define PLAYER_POS -1
# define ITEM -2

# define NORTH 5
# define WEST 44
# define EAST 72
# define SOUTH 22

# define VIEW_UP 501
# define VIEW_DOWN 502
# define VIEW_RIGHT 503
# define VIEW_LEFT 504

# define INDEX_MODE 665
# define COMPASS_MODE 666

# define MAX_MAP_SIZE 10000

# define WOLF_SPRITES 114
# define MINE_SPRITES 256
# define SPRITES_LIM 160

# define WOLF3D 0
# define MINECRAFT 1
# define MINECRAFT_ART 2

# define TILEMAPS 3

# define CONFIG_SIZE 31

# define GUN 0
# define KNIFE 1
# define DAKKA 2
# define PICKAXE 3

# define HEAD 14

# define WEAPONS_NUM 4

# define POS_UPDATE 15

# define LOOK_LIMIT 500

# define DEF_TEXTURE 1

#endif
