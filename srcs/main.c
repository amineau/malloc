/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 11:54:02 by amineau           #+#    #+#             */
/*   Updated: 2017/04/07 18:58:46 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

t_zone **g_zone = NULL;

t_alloc	*alloc_create(void *ptr, size_t size)
{
	t_alloc	*alloc;

	ft_putendl("Create alloc");
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
ft_printf("size %zu\n", size);
	if (size <= 0)
		return (NULL);
	length = length_zone(size);
	type = type_zone(length);
	if (!g_zone)
		if ((void*)(g_zone = (t_zone**)mmap(0, sizeof(t_zone*), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			ft_putendl("Error during create zone"); //error("mmap" ,errno);
	// ft_printf("errno : %d\n", errno);
	if (!*g_zone)
	{
		if (!(*g_zone = zone_create(length, type)))
			ft_putendl("Error during create zone");
		// ft_printf("errno : %d %d\n", errno, ENOMEM);
		ft_putendl("Option 1");
		(*g_zone)->alloc = alloc_create((*g_zone)->start, size);
		(*g_zone)->current = (*g_zone)->alloc;
		return ((*g_zone)->alloc->start);
	}

	tmp = *g_zone;
	while (tmp && ft_strcmp(type, "LARGE"))
	{
		if (tmp->type == type)
		{
			if ((unsigned long)tmp->current + sizeof(t_alloc) + size < (unsigned long)tmp + length)
			{
				// ft_printf("tmp*********** %p : %zu\n", tmp->current->start, tmp->current->length);
				ft_putendl("Option 2");
				tmp->current->next = alloc_create(tmp->current->start + tmp->current->length + 1, size);
				tmp->current = tmp->current->next;

				return (tmp->current->start);
			}
		}

		tmp = tmp->next;
	}
	if (!(new = zone_create(length, type)))
		ft_putendl("Error during create zone");
	zone_insert(new);
	ft_putendl("Option 3");
	new->alloc = alloc_create(new->start, size);
	new->current = new->alloc;
	return (new->alloc->start);
}

int main()
{
	char **ptr;
	int length = 1;
	int i = 0;


	while (i < 5){
		ft_putnbrendl(i);
		ptr = (char*)ft_malloc(++i);
		show_alloc_mem();
		if (i > 3) {
			ft_free(ptr);
		}
	}
	show_alloc_mem();
	ft_free(ptr);
	show_alloc_mem();
	ptr = (char*)ft_malloc(15);
	show_alloc_mem();
	// ft_free(ptr);
	// show_alloc_mem();
;
	return (0);
}
