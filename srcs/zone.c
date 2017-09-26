/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 01:08:28 by amineau           #+#    #+#             */
/*   Updated: 2017/09/14 01:28:38 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*init_zone(void)
{
	if (!g_zone)
	{
		if (!(g_zone = (t_zone**)init_page(sizeof(t_zone*))))
			return (NULL);
		*g_zone = NULL;
	}
	return ((void*)g_zone);
}

t_zone	*create_zone(size_t size)
{
	t_zone	*zone;
	size_t	init_size;
	size_t	interval;
	int		i;

	init_size = get_init_size(size);
	if (!(zone = (t_zone*)init_page(init_size)))
		return (NULL);
	zone->data = (void*)zone + ZONE_STRUCT_SIZE;
	zone->size = init_size;
	zone->block = create_block(zone->data,
	is_large(size) ? MALLOC_GUARD_EDGES && !MALLOC_DO_NOT_PROTECT_PRE_LUDE : 0);
	if (!is_large(size))
	{
		i = 1;
		interval = size_of_data(size) + BLOCK_STRUCT_SIZE;
		while (i < 100)
			create_block(zone->data + i++ * interval, 0);
	}
	return (zone);
}

void	add_zone(t_zone *zone)
{
	t_zone	*tmp;

	if (!*g_zone || *g_zone > zone)
	{
		zone->next = *g_zone;
		*g_zone = zone;
	}
	else
	{
		tmp = *g_zone;
		while (tmp->next && tmp->next < zone)
			tmp = tmp->next;
		zone->next = tmp->next;
		tmp->next = zone;
	}
}

size_t	type_zone(size_t size)
{
	if (size <= (TINY - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE)
		return (TINY);
	else if (size <= (SMALL - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE)
		return (SMALL);
	return (size);
}

t_zone	*find_zone(void *ptr)
{
	t_zone	*zone;

	if (!g_zone)
		return (NULL);
	zone = *g_zone;
	while (zone)
	{
		if (zone->data < ptr
				&& ptr < zone->data + zone->size - ZONE_STRUCT_SIZE)
			return (zone);
		zone = zone->next;
	}
	return (NULL);
}
