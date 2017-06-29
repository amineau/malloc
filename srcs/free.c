/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:01:31 by amineau           #+#    #+#             */
/*   Updated: 2017/06/07 21:55:23 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone **g_zone;


static char *strcpylength(char *dst, const char *src, size_t length)
{
	int i;

	i = 0;
	if (!src)
		return (dst);
	while (i < length)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static void	*ft_voidcpy(char *dst, const char *src, size_t length)
{
	int i;

	// ft_printf("length %zu\n", length);
	i = 0;
	if (!src)
		return (dst);
	while (i < length)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static t_alloc *ft_defrag(t_zone *zone, t_alloc *toFree)
{
	size_t	length;
	size_t	diff;
	t_alloc	*tmp;

	diff = (size_t)((void*)toFree->next - (void*)toFree);
	length = zone->current->start + zone->current->length - (void*)toFree->next; //if (toFree->next == NULL ???)
	ft_voidcpy((char*)toFree, (char*)toFree->next, length);
	tmp = toFree;
	while (tmp->next)
	{
		tmp->next = (void*)tmp->next - diff;
		tmp->start = (void*)tmp->start - diff;
		tmp = tmp->next;
	}
	tmp->start = (void*)tmp->start - diff;
	return tmp;
}

void ft_free(void *ptr)
{
	t_zone	*tmp;
	t_alloc *tmp2;
	int 	boolean;

	boolean = 1;
	tmp = *g_zone;

	while (boolean && tmp)
	{
		if (tmp->alloc->start == ptr)
		{
			if (!tmp->alloc->next)
				free_zone(tmp);
			else
				tmp->alloc = tmp->alloc->next;
			boolean = 0;
			break;
		}
		tmp2 = tmp->alloc;
		while(boolean && tmp2->next)
		{
			if (tmp2->next->start == ptr)
			{
				if (tmp2->next->next)
					tmp->current = ft_defrag(tmp, tmp2->next);
				else
				{
					tmp2->next = NULL;
					tmp->current = tmp2;
				}
				boolean = 0;
				break;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	if (boolean && ptr)
	{
		ft_putstr("malloc: *** error for object 0x");
		ft_pututoabase((uintmax_t)ptr, 16, 'a' + 23);
		ft_putendl(": pointer being freed was not allocated");
		exit(1);
	}
}
