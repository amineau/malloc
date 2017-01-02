/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:17:38 by amineau           #+#    #+#             */
/*   Updated: 2016/12/26 13:28:56 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

char 	*type_str(short type)
{
	if (type == 0)
		return ("TINY");
	if (type == 1)
		return ("SMALL");
	return ("LARGE");
}

void	show_alloc_mem(t_zone *zone)
{
	t_zone	*tmp;
	t_alloc *alloc;

	tmp = zone;
	while (tmp)
	{
		printf("%s : %p\n", type_str(zone->type), zone->start);
		alloc = tmp->alloc;
		while (alloc)
		{
			printf("%p - %p : %zu octets\n", alloc->start, alloc->start + alloc->length - 1, alloc->length);
			alloc = alloc->next;
		}
		tmp = tmp->next;
	}
}
