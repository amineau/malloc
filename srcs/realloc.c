/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:02:58 by amineau           #+#    #+#             */
/*   Updated: 2017/09/14 01:16:32 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_block *block;
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (!size)
		free(ptr);
	else if ((zone = find_zone(ptr))
		&& (block = find_block(ptr, zone)))
	{
		if (size_of_data(zone->size) < size)
		{
			new_ptr = malloc(size);
			ft_memcpy(new_ptr, block->data, size_of_data(zone->size));
			free(ptr);
			ptr = new_ptr;
		}
		else
			block->size = size;
		return (ptr);
	}
	else
		is_not_allocated(ptr, "realloc'd");
	return (NULL);
}
