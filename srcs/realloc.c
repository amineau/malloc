/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:02:58 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 17:29:50 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*find_block(void *ptr, t_zone *zone)
{
	t_block	*block;
	size_t	interval;

	interval = size_of_data(zone->size) + BLOCK_STRUCT_SIZE;
	block = zone->block;
	while (block->data < ptr)
		block = (t_block*)((size_t)block + interval);
	if (block->data == ptr)
		return (block);
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_block *block;
	void	*new_ptr;

	if (!ptr)
		return (ft_malloc(size));
	if (!size)
		ft_free(ptr);
	else if ((zone = find_zone(ptr))
		&& (block = find_block(ptr, zone)))
	{
		if (size_of_data(zone->size) < size)
		{
			new_ptr = ft_malloc(size);
			ft_memcpy(new_ptr, block->data, size_of_data(zone->size));
			ft_free(ptr);
			ptr = new_ptr;
		}
		else
			block->size = size;
		return (ptr);
	}
	return (NULL);
}
