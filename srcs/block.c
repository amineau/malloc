/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 01:12:04 by amineau           #+#    #+#             */
/*   Updated: 2017/09/26 23:31:12 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_block(t_block **addr_block, size_t size)
{
	t_block	*block;

	block = *addr_block;
	block->size = size;
	if (MALLOC_PRE_SCRIBBLE)
		ft_memset(block->data, DATA_PRE_SCRIBBLE, size);
}

t_block	*create_block(void *addr, int flag)
{
	t_block	*block;
	size_t	size_pre_data;

	size_pre_data = BLOCK_STRUCT_SIZE;
	size_pre_data += flag ? MALLOC_GUARD_EDGES : 0;
	block = (t_block*)addr;
	block->data = (void*)block + size_pre_data;
	block->size = 0;
	block->nbr_ret = 0;
	return (block);
}

t_block	*block_available(size_t type)
{
	t_zone	*tmp;
	t_block	*block;
	size_t	interval;
	int		i;

	tmp = *g_zone;
	interval = size_of_data(type) + BLOCK_STRUCT_SIZE;
	while (tmp)
	{
		if (tmp->size == type)
		{
			block = tmp->block;
			i = 0;
			while (i++ < 100)
			{
				if (!block->size)
					return (block);
				block = (t_block*)((size_t)block + interval);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_block	*find_block(void *ptr, t_zone *zone)
{
	t_block	*block;
	size_t	interval;

	interval = size_of_data(zone->size) + BLOCK_STRUCT_SIZE;
	block = zone->block;
	while (block->data && block->data < ptr)
		block = (t_block*)((size_t)block + interval);
	if (block->data && block->data == ptr && block->size)
		return (block);
	return (NULL);
}
