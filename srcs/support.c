/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:34:28 by amineau           #+#    #+#             */
/*   Updated: 2017/09/14 01:15:51 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*init_page(size_t size)
{
	void	*result;
	int		prot;
	int		flags;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	result = mmap(0, size, prot, flags, -1, 0);
	if (result == MAP_FAILED)
	{
		insufficient_memory();
		pthread_mutex_unlock(&g_mutex_stock);
		return (NULL);
	}
	return (result);
}

int		is_large(size_t type)
{
	return ((type == TINY || type == SMALL) ? 0 : 1);
}

size_t	size_of_data(size_t type)
{
	size_t	size;

	size = type - ZONE_STRUCT_SIZE;
	size = is_large(type) ? size : size / 100;
	return (size - BLOCK_STRUCT_SIZE);
}

size_t	get_init_size(size_t size)
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