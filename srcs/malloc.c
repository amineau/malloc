/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:02:16 by amineau           #+#    #+#             */
/*   Updated: 2017/09/27 00:00:50 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc_no_lock(size_t size)
{
	size_t	type;
	t_block	*block;
	t_zone	*zone;

	if (size == 0)
		return (NULL);
	type = type_zone(size);
	if (!init_zone())
		return (NULL);
	if (is_large(type) || !(block = block_available(type)))
	{
		if (!(zone = create_zone(type)))
			return (NULL);
		add_zone(zone);
		block = zone->block;
	}
	init_block(&block, size);
	if (MALLOC_STACK_LOGGING)
		block->nbr_ret = backtrace(block->buffer_stack, SIZE_BUFFER_STACK);
	return (block->data);
}

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex_stock);
	ptr = malloc_no_lock(size);
	pthread_mutex_unlock(&g_mutex_stock);
	return (ptr);
}
