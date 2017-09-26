/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:02:58 by amineau           #+#    #+#             */
/*   Updated: 2017/09/14 19:22:47 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*params_empty(void *ptr, size_t size)
{
	void	*ret;

	ret = NULL;
	if (!ptr)
		ret = malloc(size);
	else
		free(ptr);
	return (ret);
}

int		match_ptr(void *ptr, t_zone **zone, t_block **block)
{
	*zone = find_zone(ptr);
	if (*zone)
	{
		*block = find_block(ptr, *zone);
		if (*block)
			return (1);
	}
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_block *block;
	void	*new_ptr;

	if (!ptr || !size)
		return (params_empty(ptr, size));
	pthread_mutex_lock(&g_mutex_stock);
	if (match_ptr(ptr, &zone, &block))
	{
		if (size_of_data(zone->size) < size)
		{
			new_ptr = malloc_no_lock(size);
			ft_memcpy(new_ptr, block->data, size_of_data(zone->size));
			free_no_lock(ptr);
			ptr = new_ptr;
		}
		else
			block->size = size;
		pthread_mutex_unlock(&g_mutex_stock);
		return (ptr);
	}
	else
		is_not_allocated(ptr, "realloc'd");
	pthread_mutex_unlock(&g_mutex_stock);
	return (NULL);
}
