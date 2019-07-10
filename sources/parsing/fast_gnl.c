/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_gnl.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:54:48 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/08 12:06:22 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char		**fast_gnl(int fd)
{
	t_gnl_fdf	gnl;
	int 		buff_size;

	buff_size = 2000000;
	gnl.sum_len = 0;
	gnl.backup = ft_memalloc(1);
	gnl.temp_str = NULL;
	if (fd < 0 || read(fd, gnl.buf, 0) < 0)
		raise_error(ERR_INV_FILE);
	while ((gnl.read_res = read(fd, gnl.buf, buff_size)))
	{
		gnl.sum_len += gnl.read_res;
		gnl.buf[gnl.read_res] = '\0';
		gnl.temp_str = ft_strljoin(gnl.backup, gnl.buf, gnl.sum_len);
		free(gnl.backup);
		gnl.backup = gnl.temp_str;
	}
	gnl.result = ft_strsplit(gnl.temp_str, '\n');
	free(gnl.temp_str);
	return (gnl.result);
}