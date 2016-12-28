/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 11:54:02 by amineau           #+#    #+#             */
/*   Updated: 2016/12/26 19:48:09 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

short 	type_zone(size_t size)
{
	if (size == TINY)
		return (0);
	else if (size == SMALL)
		return (1);
	return (2);
}

t_zone	*zone_create(size_t size, short type)
{
	t_zone	*zone;

	if (!(zone = (t_zone*)mmap(0, sizeof(t_zone), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
	|| !(zone->start = (void*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	zone->type = type;
	zone->next = NULL;
	printf("******Create zone type %d, start in %p, end in %p*******\n", type, zone->start, zone->start + size);
	return (zone);
}

size_t	length_zone(size_t size)
{
	if (size * 100 <= TINY)
		return (TINY);
	else if (size * 100 <= SMALL)
		return (SMALL);
	return (size);
}

t_alloc	*alloc_create(void *ptr, size_t size)
{
	t_alloc	*alloc;
	printf("******Create alloc in %p length : %zu*******\n", ptr, size);

	if (!(alloc = (t_alloc*)mmap(0, sizeof(t_alloc), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
	 || !(alloc->start = (void*)mmap(0, sizeof(void), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	alloc->start = ptr;
	alloc->length = size;
	return (alloc);
}

t_zone 	*get_static()
{
	static t_zone 	*zone;
	return zone;
}

void	*ft_malloc(size_t size)
{
	static t_zone 	*zone;
	t_zone 	*new;
	t_zone 	*tmp;
	t_alloc *alloc;
	short 	type;
	size_t	length;

	if (size <= 0)
		return (NULL);
	length = length_zone(size);
	type = type_zone(length);
	// printf("\tlength : %zu\n\tsize : %zu\n\ttype : %d\n", length, size, type);
	
	if (!zone)
	{
		if (!(zone = zone_create(length, type)))
			printf("Error during create zone\n");
		if (!(zone->alloc = alloc_create(zone->start, size)))
			printf("Error during create alloc\n");
		return (zone->alloc->start);
	}

	tmp = zone;
	while (tmp && type != 2)
	{
		if (tmp->type == type)
		{
			if ((alloc = tmp->alloc))
			{
				while (alloc->next)
					alloc = alloc->next;
				if (alloc->start + alloc->length + size < tmp->start + length)
				{
					if (!(alloc->next = alloc_create(alloc->start + alloc->length + 1, size)))
						printf("Error during create alloc\n");
					return (alloc->next->start);
				}
			}
			else
			{
				if (!(tmp->alloc = alloc_create(tmp->start, size)))
						printf("Error during create alloc\n");
				return (tmp->alloc->start);
			}
		}
		tmp = tmp->next;
	}
	if (!(new = zone_create(length, type))) 
		printf("Error during create zone\n");
	tmp = zone;
	while (tmp->next)
	{
		if (tmp->start < new->start && new->start < tmp->next->start)
		{
			new->next = tmp->next;
			tmp->next = new;
			break;
		}
	}
	if (!tmp->next)
		tmp->next = new;
	if (!(new->alloc = alloc_create(new->start, size)))
		printf("Error during create alloc\n");
	return (new->alloc->start);
}

# include "libft.h"
int main()
{
	printf("*************\nTINY : %d\nSMALL : %d\n", TINY, SMALL);
	char *str;
	// int length = 1;
	int i = 0;
	while (i++ < 100)
	{
		str = (char*)ft_malloc(4096);
		str[0] = '\0';
		// printf("address of pointer : %p\n", str);
	}
	// ft_printf("%d\n", TINY);
	return (0);
}
