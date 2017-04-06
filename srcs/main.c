/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 11:54:02 by amineau           #+#    #+#             */
/*   Updated: 2017/04/06 19:41:52 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_zone **g_zone = NULL;

t_alloc	*alloc_create(void *ptr, size_t size)
{
	t_alloc	*alloc;

	alloc = (t_alloc*)ptr;
	alloc->start = (void*)alloc + sizeof(t_alloc);
	alloc->length = size;
	alloc->next = NULL;
	return (alloc);
}

void	*ft_malloc(size_t size)
{
	t_zone 	*new;
	t_zone 	*tmp;
	char 	*type;
	size_t	length;

	if (size <= 0)
		return (NULL);
	length = length_zone(size);
	type = type_zone(length);
	if (!g_zone)
	{
		if (!(g_zone = (t_zone**)mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
		 || !(*g_zone = zone_create(length, type)))
			write(1, "Error during create zone\n", 25);
		(*g_zone)->alloc = alloc_create((*g_zone)->start, size);
		(*g_zone)->current = (*g_zone)->alloc;
		return ((*g_zone)->alloc->start);
	}

	tmp = *g_zone;
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

int main()
{
	// printf("*************\nTINY : %d\nSMALL : %d\n", TINY, SMALL);
	char *str;
	char *ptr;
	char *otr;
	// int length = 1;
	int i = 1;

	otr = (char*)ft_malloc(2);
	otr[0] = 'o';
	otr[1] = '\0';
	while (i++ < 5)
	{
		str = (char*)ft_malloc(i);
		str[0] = 's';
		str[1] = '\0';
	}
	while (--i > 1)
	{
		ptr = (char*)ft_malloc(i);
		ptr[0] = 'p';
		ptr[1] = '\0';
	}
	show_alloc_mem();
	ft_printf("ptr : %p, %s\n", ptr, ptr);
	ft_free(otr);
	ft_free(ptr);
	ft_printf("ptr : %p, %s\n", ptr, ptr);
	ft_printf("str : %p, %s\n", str, str);
	ft_free(str);
	ft_printf("str : %p, %s\n", str, str);
	show_alloc_mem();
	return (0);
}
