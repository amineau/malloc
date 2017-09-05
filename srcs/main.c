/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:34:28 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 11:47:59 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone **g_zone = NULL;

void	*init_page(size_t size)
{
	void *result;
	int prot;
	int flags;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	result = mmap(0, size, prot, flags, -1, 0);
	if (result == MAP_FAILED)
		return (NULL);
	return (result);
}

size_t	size_of_data(size_t type)
{
	size_t size;

	size = type - ZONE_STRUCT_SIZE;
	size = (type > SMALL) ? size : size / 100;
	return (size - BLOCK_STRUCT_SIZE);
}

t_block	*create_block(void *addr, size_t type)
{
	t_block	*block;
	
	block = (t_block*)addr;
	block->data = (void*)block + BLOCK_STRUCT_SIZE;
	block->size = 0;
	return (block);
}

t_zone	*create_zone(size_t size)
{
	t_zone	*zone;
	t_block	*block;
	size_t	initSize;
	size_t	interval;
	int		i;

	initSize = size;
	initSize += (size > SMALL) ? BLOCK_STRUCT_SIZE : 0 ;
	if (!(zone = (t_zone*)init_page(initSize)))
		return (NULL);
	zone->data = (void*)zone + ZONE_STRUCT_SIZE;
	zone->size = initSize;
	zone->block = create_block(zone->data, zone->size);
	if (size <= SMALL)
	{
		i = 1;
		interval = size_of_data(size) + BLOCK_STRUCT_SIZE;
		while(i < 100)
			create_block(zone->data + i++ * interval, zone->size);
	}
	return zone;
}

void	add_zone(t_zone *zone)
{
	zone->next = *g_zone;
	*g_zone = zone;
}

size_t	type_zone(size_t size)
{
	if (size <= (TINY - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE)
		return (TINY);
	else if (size <= (SMALL - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE)
		return (SMALL);
	return (size);
}

t_block	*block_available (size_t type)
{
	t_zone	*tmp;
	t_block	*block;
	size_t	interval;
	int i;

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

void	*ft_malloc(size_t size)
{
	size_t	type;
	t_block	*block;

	if (size <= 0)
		return (NULL);
	if (!g_zone)
	{
		if (!(g_zone = (t_zone**)init_page(sizeof(t_zone*))))
			return (NULL);
		*g_zone = NULL;
	}
	type = type_zone(size);
	if (type > SMALL || !(block = block_available(type)))
	{
		add_zone(create_zone(type));
		block = (*g_zone)->block;
	}
	block->size = size;
	return (block->data);
}

void tests ()
{
	assert(init_page(0) == NULL);
	assert(init_page(1000) != NULL);

	assert(type_zone(0) == TINY);
	assert(type_zone((TINY - ZONE_STRUCT_SIZE) / 200 - BLOCK_STRUCT_SIZE) == TINY);
	assert(type_zone(TINY / 100) == SMALL);
	assert(type_zone(SMALL / 100) == SMALL / 100);

	assert(size_of_data(TINY) == (TINY - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE);
	assert(size_of_data(SMALL) == (SMALL - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE);
	assert(size_of_data(SMALL + 1) == SMALL + 1 - BLOCK_STRUCT_SIZE - ZONE_STRUCT_SIZE);

	void *addr = init_page(SMALL * 2);
	t_block *block = create_block(addr, TINY);
	assert((size_t)block->data == (size_t)addr + BLOCK_STRUCT_SIZE);
	assert(block->size == 0);

	block = create_block(addr, SMALL);
	assert((size_t)block->data == (size_t)addr + BLOCK_STRUCT_SIZE);
	assert(block->size == 0);

	block = create_block(addr, SMALL + 1);
	assert((size_t)block->data == (size_t)addr + BLOCK_STRUCT_SIZE);
	assert(block->size == 0);

	t_zone *zone = create_zone(TINY);
	assert(zone->size == TINY);
	assert((size_t)zone->data == (size_t)zone + ZONE_STRUCT_SIZE);
	int i = 0;
	size_t interval = size_of_data(TINY) + BLOCK_STRUCT_SIZE;
	for(size_t a = (size_t)zone->data; a < (size_t)zone->data + zone->size - ZONE_STRUCT_SIZE - interval; a += interval)
	{
		block = (t_block*)a;
		assert((size_t)block->data == a + BLOCK_STRUCT_SIZE);
		assert(block->size == 0);
	}

	zone = create_zone(SMALL);
	assert(zone->size == SMALL);
	assert((size_t)zone->data == (size_t)zone + ZONE_STRUCT_SIZE);
	i = 0;
	interval = size_of_data(SMALL) + BLOCK_STRUCT_SIZE;
	for(size_t a = (size_t)zone->data; a < (size_t)zone->data + zone->size - ZONE_STRUCT_SIZE - interval; a += interval)
	{
		block = (t_block*)a;
		assert((size_t)block->data == a + BLOCK_STRUCT_SIZE);
		assert(block->size == 0);
	}
}

int main()
{
	printf("TINY = %d\nSMALL = %d\nBLOCK_SIZE = %zu\nZONE_SIZE = %zu\n", TINY, SMALL, BLOCK_STRUCT_SIZE, ZONE_STRUCT_SIZE);
	tests();
	ft_malloc(50000);
	ft_malloc(50000);
	show_alloc_mem();
	return (0);
}

