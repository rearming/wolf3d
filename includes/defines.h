/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:24:54 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/25 16:00:07 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifdef __APPLE__
#  define WIN_WIDTH 1980
#  define WIN_HEIGHT 1020

#  define SCALE_WIDTH 1.328
#  define SCALE_HEIGHT 1.274

# else
#  define WIN_WIDTH 1980
#  define WIN_HEIGHT 1020
# endif

# define TRUE 1
# define FALSE 0

# define PLAYER_POS -1
# define ITEM -2

# define BMP_IMG 100
# define STB_IMG 101

# define SVA_FLAG 5
# define ROCK_WALL 1
# define HITLER 96
# define RED_BRICKS 72
# define SVA_EAGLE 11
# define WOOD 22

# define VIEW_UP 501
# define VIEW_DOWN 502
# define VIEW_RIGHT 503
# define VIEW_LEFT 504

# define NUMBER_MODE 665
# define COMPASS_MODE 666

# define MAX_MAP_SIZE 10000

# define MOVING 667
# define IDLE 668

# define WOLF_SPRITES 114
# define MINE_SPRITES 256

# define WOLF3D 0
# define MINECRAFT 1
# define MINECRAFT_ART 2

# define TILEMAPS 3

# define CONFIG_SIZE 30

# define GUN 0
# define KNIFE 1
# define DAKKA 2
# define PICKAXE 3

# define WEAPONS_NUM 4

# define POS_UPDATE 30

# define TERM_MEM_SIZE 10
# define TERM_CMD_SIZE 100

# define DELETE "Backspace"
# define SPACE "Space"

#endif
