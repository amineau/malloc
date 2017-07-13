#include "malloc.h"

t_zone **g_zone = NULL;

void	*init_page(size_t size)
{
	void *result;

	result = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (result == MAP_FAILED);
		return (NULL);
	return (result);
}

size_t	size_of_data(size_t type)
{
	size_t size;
	if (type <= SMALL)
		size = (type - (100 * BLOCK_STRUCT_SIZE)) / 100;
	else size = type;
	return size;
}

t_block	*create_block(t_block *block, size_t type)
{
	// new = (t_block*)(block + BLOCK_STRUCT_SIZE + block->size);;
	// to call in parent function
	
	block->data = (void*)(block + BLOCK_STRUCT_SIZE);
	block->size = size_of_data(type);
	block->free = 1;
	block->next = NULL;
}

t_zone	*create_zone(size_t size)
{
	t_zone *new;

	if (size > SMALL)
		size += BLOCK_STRUCT_SIZE;
	new = (t_zone*)init_page(size);
	else
		new = (t_zone*)init_page(size + BLOCK_STRUCT_SIZE);
	if (new)
	{
		new->zone = size;
		// create 1 or 100 blocks pleaze
	}
	return new;
}

size_t	type_zone(size_t size)
{
	if (size <= TINY - 100 * BLOCK_STRUCT_SIZE)
		return (TINY);
	else if (size <= SMALL - 100 * BLOCK_STRUCT_SIZE)
		return (SMALL);
	return (size);
}

void	*ft_malloc(size_t size)
{
	size_t	length_zone;

	if (size_t <= 0)
		return (NULL);
	if (!g_zone)
		if (!(g_zone = (t_zone**)init_page(sizeof(t_zone*))))
			return (NULL);
	type_zone = type_zone(size);
	if (!(*g_zone))
		*g_zone = create_zone(type_zone);

	while (*g_zone)
	{
		//find_block
		*g_zone = *(g_zone->next);
	}
	



}

int main()
{
	
}
