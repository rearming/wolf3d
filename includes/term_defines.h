/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:43:27 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/27 19:25:39 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_DEFINES_H
# define TERM_DEFINES_H

# define TERM_MEM_SIZE 10
# define TERM_BUFF_SIZE 100
# define TERM_CMD_LEN 20

# define DELETE "Backspace"
# define SPACE "Space"
# define ARR_LEFT "Left"
# define ARR_RIGHT "Right"

/*
**	terminal commands
*/

# define INV_COMMAND 0
# define MIN_COMMAND_SIZE 3

/*
**	basic commands
*/

# define RENDER 1
# define SET 2
# define PLAYER 3
# define CHANGE 4
/*
**	targets
*/

# define ALL 100
# define BLOCK 101
# define LOOK 102
# define TELEPORT 103
# define COLORS 104
# define CHANNELS 105
# define FOV 106

/*
**	arguments
*/

# define FREEZE 10
# define UNFREEZE 11
# define DEFAULT 12

# define MIAMI 13

#endif
