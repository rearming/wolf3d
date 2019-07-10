/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:01:21 by sleonard          #+#    #+#             */
/*   Updated: 2019/07/10 13:39:37 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !(*alst))
		return ;
	while (*alst)
	{
		del(*alst, (*alst)->content_size);
		*alst = (*alst)->next;
	}
}
