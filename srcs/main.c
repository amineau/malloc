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
<<<<<<< HEAD
=======
	// printf("******Create alloc in %p length : %zu*******\n", ptr, size);
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129

	alloc = (t_alloc*)ptr;
	alloc->start = (void*)alloc + sizeof(t_alloc);
	alloc->length = size;
	return (alloc);
}

void	*ft_malloc(size_t size)
{
<<<<<<< HEAD
=======
	static t_zone 	**zone;
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129
	t_zone 	*new;
	t_zone 	*tmp;
	char 		*type;
	size_t	length;

	if (size <= 0)
		return (NULL);
	length = length_zone(size);
	type = type_zone(length);
<<<<<<< HEAD
	
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
=======
	// printf("\tlength : %zu\n\tsize : %zu\n\ttype : %d\n", length, size, type);
	zone = get_static();
	if (!*zone)
	{
		if (!(*zone = zone_create(length, type)))
			printf("Error during create zone\n");
		if (!((*zone)->alloc = alloc_create((*zone)->start, size)))
			printf("Error during create alloc\n");
		return ((*zone)->alloc->start);
	}

	tmp = *zone;
	while (tmp && type != 2)
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129
	{
		if (tmp->type == type)
		{
				// printf("+ %lld\n", (long long int)tmp + length - ((long long int)tmp->current + sizeof(t_alloc) + size));
			if ((long unsigned int)tmp->current + sizeof(t_alloc) + size < (long unsigned int)tmp + length)
			{
<<<<<<< HEAD
				tmp->current->next = alloc_create(tmp->current->start + tmp->current->length + 1, size);
				tmp->current = tmp->current->next;
				return (tmp->current->start);
=======
				while (alloc->next)
					alloc = alloc->next;
				if (alloc->start + alloc->length + size < tmp->start + length)
				{
					if (!(alloc->next = alloc_create(alloc->start + alloc->length, size)))
						printf("Error during create alloc\n");
					return (alloc->next->start);
				}
			}
			else
			{
				if (!(tmp->alloc = alloc_create(tmp->start, size)))
						printf("Error during create alloc\n");
				return (tmp->alloc->start);
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129
			}
		}
		tmp = tmp->next;
	}

	if (!(new = zone_create(length, type))) 
<<<<<<< HEAD
		write(1, "Error during create zone\n", 25);
	zone_insert(new);
	new->alloc = alloc_create(new->start, size);
	new->current = new->alloc;
	return (new->alloc->start);
=======
		printf("Error during create zone\n");
	tmp = *zone;
		printf("toto008\n");
	while (tmp)
	{
		printf("toto007\n");
		if (tmp->start > new->start
			|| (tmp->start < new->start
				&& (!tmp->next || new->start < tmp->next->start)))
		{
			printf("toto0\n");
			if (tmp->start > new->start)
			{
				new->next = tmp->start;
				*zone = new;
				printf("toto1\n");
			}
			else
			{
				new->next = tmp->next;
				tmp->next = new;
				printf("toto2\n");
			}
			if (!(new->alloc = alloc_create(new->start, size)))
				printf("Error during create alloc\n");
			printf("toto3\n");
			return (new->alloc->start);
		}
		tmp = tmp->next;
	}
	return (NULL);
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129
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
<<<<<<< HEAD
	while (i++ < 30)
	{
		str = (char*)ft_malloc(i);
		// printf("%d\n", i);
		str[0] = '\0';
	}
	while (--i > 1)
=======
	while (i < 180)
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129
	{
		str = (char*)ft_malloc(i);
		// printf("%d\n", i);
		str[0] = '\0';
<<<<<<< HEAD
	}
	str[0] = 'a';
	str[1] = '\0';
	show_alloc_mem();
	// ft_free(str);
	show_alloc_mem();
=======
		// show_alloc_mem(*get_static());
		i++;
		// printf("address of pointer : %p\n", str);
	}
	show_alloc_mem(*get_static());
	// ft_printf("%d\n", TINY);
>>>>>>> 723bde1f0907ae766fca610359143cfcf2e2e129
	return (0);
}
