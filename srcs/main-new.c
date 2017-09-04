/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:34:28 by amineau           #+#    #+#             */
/*   Updated: 2017/09/04 19:15:03 by amineau          ###   ########.fr       */
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
	block->size = size_of_data(type);
	block->free = 1;
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
		interval = size_of_data(size);
		while(i < 100)
			create_block(zone->data + i++ * interval, zone->size);
	}
	return zone;
}

size_t	type_zone(size_t size)
{
	if (size <= (TINY - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE)
		return (TINY);
	else if (size <= (SMALL - ZONE_STRUCT_SIZE) / 100 - BLOCK_STRUCT_SIZE)
		return (SMALL);
	return (size);
}

void	*ft_malloc(size_t size)
{
	size_t	length_zone;

	if (size <= 0)
		return (NULL);
	if (!g_zone)
		if (!(g_zone = (t_zone**)init_page(sizeof(t_zone*))))
			return (NULL);
	length_zone = type_zone(size);
	if (!(*g_zone))
		*g_zone = create_zone(length_zone);

	// while (*g_zone)
	// {
	// 	//find_block
	// 	*g_zone = *(g_zone->next);
	// }
	
	return (NULL);


}

int main()
{
	// UNIT TEST
	printf("TINY = %d\nSMALL = %d\n", TINY, SMALL);

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
	assert(block->size = size_of_data(TINY));
	assert(block->free == 1);

	block = create_block(addr, SMALL);
	assert((size_t)block->data == (size_t)addr + BLOCK_STRUCT_SIZE);
	assert(block->size = size_of_data(SMALL));
	assert(block->free == 1);

	block = create_block(addr, SMALL + 1);
	assert((size_t)block->data == (size_t)addr + BLOCK_STRUCT_SIZE);
	assert(block->size = size_of_data(SMALL + 1));
	assert(block->free == 1);

	t_zone *zone = create_zone(TINY);
	assert(zone->size == TINY);
	assert((size_t)zone->data == (size_t)zone + ZONE_STRUCT_SIZE);
	int i = 0;
	for(size_t a = (size_t)zone->data; a < (size_t)zone->data + zone->size - ZONE_STRUCT_SIZE; a += size_of_data(TINY))
	{
		block = (t_block*)a;
		printf("%d -- %zu\n", i++, (size_t)zone->data + zone->size - ZONE_STRUCT_SIZE - a);
		assert((size_t)block->data == a + BLOCK_STRUCT_SIZE);
		assert(block->size = size_of_data(TINY));
		assert(block->free == 1);
	}

	
	/************** END TESTS **************/
	return (0);
}
