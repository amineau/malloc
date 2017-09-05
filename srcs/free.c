/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:01:31 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 11:39:02 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone **g_zone;

t_zone	*find_zone(void *ptr)
{
	t_zone	*zone;

	zone = *g_zone;
	while (zone)
	{
		if (zone->data < ptr && ptr < zone->data + zone->size - ZONE_STRUCT_SIZE)
			return (zone);
		zone = zone->next;
	}
	return (NULL);
}

int		is_empty(t_zone *zone)
{
	int 	i;
	int 	loop;
	size_t	interval;
	t_block	*block;

	interval = size_of_data(zone->size) + BLOCK_STRUCT_SIZE;	
	block = zone->block;
	i = 0;
	loop = (zone->size > SMALL) ? 1 : 100;
	while (i++ < loop)
	{
		if (block->size)
			return (0);
		block = (t_block*)((size_t)block + interval);
	}
	return (1);
}

void	free_zone (t_zone *zone)
{
	t_zone	*tmp;


	tmp = *g_zone;
	if (zone == tmp)
	{
		*g_zone = zone->next;
		munmap(zone, zone->size);	
	}
	else
	{
		while (tmp->next)
		{
			if (tmp->next == zone)
			{
				tmp->next = tmp->next->next;
				munmap((void*)zone, zone->size);
				break;
			}
			tmp = tmp->next;
		}
	}
}

void	ft_free(void *ptr)
{
	t_zone	*zone;
	t_block	*block;
	size_t	interval;
	
	if ((zone = find_zone(ptr)))
	{
		interval = size_of_data(zone->size) + BLOCK_STRUCT_SIZE;
		block = zone->block;
		while (block->data < ptr)
			block = (t_block*)((size_t)block + interval);
		if (block->data == ptr)
			block->size = 0;
		if (is_empty(zone))
			free_zone(zone);
	}
}
