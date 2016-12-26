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

t_zone const	*zones(void)
{
	static t_zone	*zone;

	if (!zone)
	{
		if (!(zone = (t_zone*)mmap(0, sizeof(t_zone), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
		|| !(zone->tiny = (t_zone_tiny*)mmap(0, sizeof(t_zone_tiny), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
		|| !(zone->small = (t_zone_small*)mmap(0, sizeof(t_zone_small), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
			return (NULL);
		zone->tiny->max = TINY;
		zone->small->max = SMALL;
		if (!(zone->tiny->zone = (void*)mmap(0, sizeof(void), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
		|| !(zone->small->zone = (void*)mmap(0, sizeof(void), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
			return (NULL);
		zone->tiny->next = NULL;
		zone->small->next = NULL;
		zone->tiny->position = zone->tiny->zone;
		zone->small->position = zone->small->zone;
	}
	return (zone);
}

size_t	lenght_zone(size_t size)
{
	if (size <= 0)
		return (NULL);
	else if (size * 100 <= TINY)
		return (TINY);
	else if (size * 100 <= SMALL)
		return (SMALL);
	return (size);
}

t_malloc	*alloc(void *ptr, size_t size)
{
	t_malloc	*alloc;

	if (!(alloc = (t_malloc*)mmap(0, sizeof(t_malloc), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
	 || !(alloc->start = (void*)mmap(0, sizeof(void), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
	 || !(alloc->end = (void*)mmap(0, sizeof(end), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	alloc->start = ptr;
	alloc->end = ptr + size;
	return (alloc);
}

void	*test(size_t size)
{
	size_t	lenght;
	t_zone	*zone;
	t_zone	*tmp;
	t_malloc	*tmp_alloc;

	zone = zones();
	tmp = zone;
	if (!(lenght = lenght_zone(size)))
		return (NULL);
	// Branche ou size est compris entre 1 et n
	if (lenght == TINY)
	{
		// Trouver le premier maillon ou la taille peut rentrer
		while (tmp->tiny && tmp->tiny->max < size)
			tmp->tiny->next = tmp->tiny;
		// Si ce maillon existe, ajouter l'allocation a ce maillon
		if (tmp->tiny)
		{
			tmp_alloc = tmp->tiny->alloc;
			// Parcours des allocations du maillon TINY (dans alloc (t_malloc*))
			while (tmp_alloc && tmp_alloc->next && tmp_alloc->next->end - tmp_alloc->start < size)
				tmp_alloc = tmp_alloc->next;
			if (tmp_alloc)
			{
				//
			}
		}
		// S'il n'existe pas, en creer un, puis ajouter l'allocation
		else
		{

		}
	}


	return (0);
}

int main()
{
	int i = 0;
	
	while (i++ < 5)
		test(i + 65);
	ft_printf("%d\n", TINY);
	return (0);
}
