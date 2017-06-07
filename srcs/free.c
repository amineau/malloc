/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:01:31 by amineau           #+#    #+#             */
/*   Updated: 2017/04/07 16:43:53 by amineau          ###   ########.fr       */
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
// if last, change current alloc in g_zone
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
				toFree = tmp2->next;
				tmp2->next = tmp2->next->next;
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
