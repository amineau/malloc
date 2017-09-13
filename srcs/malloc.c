/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:02:16 by amineau           #+#    #+#             */
/*   Updated: 2017/09/14 01:14:53 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone	**g_zone = NULL;
pthread_mutex_t g_mutex_stock = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	size_t	type;
	t_block	*block;
	t_zone	*zone;

	if (size == 0)
		return (NULL);
	type = type_zone(size);
	pthread_mutex_lock(&g_mutex_stock);
	if (!init_zone())
		return (NULL);
	if (is_large(type) || !(block = block_available(type)))
	{
		if (!(zone = create_zone(type)))
			return (NULL);
		add_zone(zone);
		block = (*g_zone)->block;
	}
	init_block(&block, size);
	pthread_mutex_unlock(&g_mutex_stock);
	if (MALLOC_STACK_LOGGING)
		block->nbr_ret = backtrace(block->buffer_stack, SIZE_BUFFER_STACK);
	return (block->data);
}
