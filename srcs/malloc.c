/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:02:16 by amineau           #+#    #+#             */
/*   Updated: 2017/09/10 16:46:12 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

size_t 	get_init_size(size_t size)
{
	if (is_large(size))
	{
		size += BLOCK_STRUCT_SIZE;
		if (!MALLOC_DO_NOT_PROTECT_PRE_LUDE)
			size += MALLOC_GUARD_EDGES;
		if (!MALLOC_DO_NOT_PROTECT_POST_LUDE)
			size += MALLOC_GUARD_EDGES;
	}
	return (size);
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

void	init_block(t_block **addr_block, size_t size)
{
	t_block	*block;

	block = *addr_block;
	block->size = size;
	if (MALLOC_PRE_SCRIBBLE)
		ft_memset(block->data, DATA_PRE_SCRIBBLE, size);
	if (MALLOC_STACK_LOGGING)
		block->nbr_ret = backtrace(block->buffer_stack, SIZE_BUFFER_STACK);
}

void	*malloc(size_t size)
{
	size_t	type;
	t_block	*block;
	t_zone	*zone;

	if (size == 0)
		return (NULL);
	if (!g_zone)
	{
		if (!(g_zone = (t_zone**)init_page(sizeof(t_zone*))))
			return (NULL);
		*g_zone = NULL;
	}
	type = type_zone(size);
	if (is_large(type) || !(block = block_available(type)))
	{
		if (!(zone = create_zone(type)))
			return (NULL);
		add_zone(zone);
		block = (*g_zone)->block;
	}
	init_block(&block, size);
	return (block->data);
}
