/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:34:28 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 17:30:37 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone	**g_zone = NULL;

void	*init_page(size_t size)
{
	void	*result;
	int		prot;
	int		flags;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	result = mmap(0, size, prot, flags, -1, 0);
	if (result == MAP_FAILED)
		return (NULL);
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
