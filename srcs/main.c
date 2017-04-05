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

t_zone *g_zone = NULL; // ajouter **

t_alloc	*alloc_create(void *ptr, size_t size)
{
	t_alloc	*alloc;

	alloc = (t_alloc*)ptr;
	alloc->start = (void*)alloc + sizeof(t_alloc);
	alloc->length = size;
	return (alloc);
}

void	*ft_malloc(size_t size)
{
	t_zone 	*new;
	t_zone 	*tmp;
	char 		*type;
	size_t	length;

	if (size <= 0)
		return (NULL);
	length = length_zone(size);
	type = type_zone(length);
	if (!g_zone)
	{
		if (!(g_zone = zone_create(length, type)))
			write(1, "Error during create zone\n", 25);
		g_zone->alloc = alloc_create(g_zone->start, size);
		g_zone->current = g_zone->alloc;
		return (g_zone->alloc->start);
	}

	tmp = g_zone;
	while (tmp && ft_strcmp(type, "LARGE"))
	{
		if (tmp->type == type)
		{
				// printf("+ %lld\n", (long long int)tmp + length - ((long long int)tmp->current + sizeof(t_alloc) + size));
			if ((long unsigned int)tmp->current + sizeof(t_alloc) + size < (long unsigned int)tmp + length)
			{
				tmp->current->next = alloc_create(tmp->current->start + tmp->current->length + 1, size);
				tmp->current = tmp->current->next;
				return (tmp->current->start);
			}
		}
		tmp = tmp->next;
	}

	if (!(new = zone_create(length, type))) 
		write(1, "Error during create zone\n", 25);
	zone_insert(new);
	new->alloc = alloc_create(new->start, size);
	new->current = new->alloc;
	return (new->alloc->start);
}

void	ft_free(char *ptr)
{
	t_alloc *alloc;

	alloc = (t_alloc*)ptr - sizeof(t_alloc);
	ft_printf("***%zu***", alloc->length);
}

int main()
{
	// printf("*************\nTINY : %d\nSMALL : %d\n", TINY, SMALL);
	char *str;
	// int length = 1;
	int i = 0;

	while (i++ < 30)
	{
		str = (char*)ft_malloc(i);
		// printf("%d\n", i);
		str[0] = '\0';
	}
	while (--i > 1)
	{
		str = (char*)ft_malloc(i);
		// printf("%d\n", i);
		str[0] = '\0';
	}
	str[0] = 'a';
	str[1] = '\0';
	show_alloc_mem();
	// ft_free(str);
	show_alloc_mem();
	return (0);
}
