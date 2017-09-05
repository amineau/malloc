/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:41:09 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 16:43:36 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*block_available (size_t type);
size_t	type_zone(size_t size);
void	add_zone(t_zone *zone);
t_zone	*create_zone(size_t size);
t_block	*create_block(void *addr, size_t type);
size_t	size_of_data(size_t type);
int		is_large (size_t type);
void	*init_page(size_t size);


void unit()
{
	assert(init_page(0) == NULL);
	assert(init_page(1000) != NULL);

	assert(is_large(TINY) == 0);
	assert(is_large(SMALL) == 0);
	assert(is_large(5000) == 1);

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

int main ()
{
    unit();
    return (0);
}