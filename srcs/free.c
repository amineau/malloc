/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:01:31 by amineau           #+#    #+#             */
/*   Updated: 2017/04/06 19:39:54 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone **g_zone;

void ft_free(void *ptr)
{
	t_zone	*tmp;
	t_alloc *tmp2;
	t_alloc *toFree;
	int 	boolean;

	boolean = 1;
	tmp = *g_zone;
	while (boolean && tmp)
	{
		tmp2 = tmp->alloc;
		if (tmp2->start == ptr)
		{
			tmp->alloc = tmp2->next;
			ft_bzero((void*)tmp2, sizeof(t_alloc) + tmp2->length);
			boolean = 0;
		}
		while(boolean && tmp2->next)
		{
			if (tmp2->next->start == ptr)
			{
				toFree = tmp2->next;
				tmp2->next = tmp2->next->next;
				ft_bzero((void*)toFree, sizeof(t_alloc) + toFree->length);
				boolean = 0;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
