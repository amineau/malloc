/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 11:54:02 by amineau           #+#    #+#             */
/*   Updated: 2017/01/28 19:48:09 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone *g_zone;

t_zone	*zone_create(size_t size, char *type)
{
	t_zone	*zone;

	if (!(zone = (t_zone*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	zone->start = (void*)zone + sizeof(t_zone);
	zone->type = type;
	zone->next = NULL;
	// printf("******Create zone type %d, start in %p, end in %p*******\n", type, zone->start, zone + size);
	return (zone);
}

void		zone_insert(t_zone *zone)
{
	t_zone *tmp;

	// if (!zone)
	// 	return(void);
	tmp = g_zone;
	if (tmp > zone)
	{
		zone->next = g_zone;
		g_zone = zone;
	}
	else
	{
		while (tmp->next)
		{
			if (tmp->start < zone->start && zone->start < tmp->next->start)
			{
				zone->next = tmp->next;
				tmp->next = zone;
				break;
			}
			tmp = tmp->next;
		}
		if (!tmp->next)
			tmp->next = zone;
	}
}

// void		delete_zone(t_zone *zone)
// {
// 	size_t size;
// 	// if (!zone)
//  // 	return(void);
// 	if (ft_strcmp(zone->type, "LARGE"))
// }