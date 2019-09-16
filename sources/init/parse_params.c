/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:13:20 by sleonard          #+#    #+#             */
/*   Updated: 2019/09/16 14:22:05 by bbear            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**parse_params(char **argv, int argc)
{
	char	**config_args;
	int		fd;
	int		config_size;

	config_args = NULL;
	if (argc > 3 && argc < 2)
		raise_error(ERR_INV_ARGS);
	if (!ft_strstr(argv[1], "wolf_config.wolf"))
		raise_error(ERR_INV_ARGS);
	fd = open(argv[1], O_RDONLY);
	if (!(config_args = fast_gnl(fd)))
		raise_error(ERR_INV_FILE);
	config_size = 0;
	while (config_args[config_size])
		config_size++;
	if (config_size != CONFIG_SIZE)
		raise_error(ERR_INV_CONFIG_SIZE);
	close(fd);
	return (config_args);
}
