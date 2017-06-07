/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:17:38 by amineau           #+#    #+#             */
/*   Updated: 2017/04/08 10:57:12 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_zone **g_zone;

void	show_alloc_mem()
{
	t_zone *tmp;
	t_alloc *tmp2;
	size_t size;

	size = 0;
	if (g_zone)
	{
		tmp = *g_zone;
		while (tmp)
		{
			// ft_printf("%s : %p\n", tmp->type, tmp->start);
			ft_putstr(tmp->type);
			ft_putstr(" : 0x");
			ft_pututoabaseendl((uintmax_t)tmp->start, 16, 'a' + 23);
			tmp2 = tmp->alloc;
			while(tmp2)
			{
				// ft_printf("\ntmp->start %zu\n", (uintmax_t)tmp2->start);
				ft_putstr("0x");
				ft_pututoabase((uintmax_t)tmp2->start, 16, 'a' + 23);
				ft_putstr(" - 0x");
				ft_pututoabase((uintmax_t)(tmp2->start + tmp2->length), 16, 'a' + 23);
				ft_putstr(" : ");
				ft_putunsi(tmp2->length);
				ft_putstr(" octet");
				if (tmp2->length != 1)
					ft_putchar('s');
				ft_putendl("");
				size += tmp2->length;
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
	}
	ft_putstr("Total : ");
	ft_putunsi(size);
	ft_putstr(" octet");
	if (size > 1)
		ft_putchar('s');
	ft_putendl("");
}
