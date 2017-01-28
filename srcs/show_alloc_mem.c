/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:17:38 by amineau           #+#    #+#             */
/*   Updated: 2016/12/26 13:28:56 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_zone *g_zone;

void	show_alloc_mem()
{
	t_zone *tmp;
	size_t size;

	size = 0;
	tmp = g_zone;
	while (tmp)
	{
		// ft_printf("%s : %p\n", tmp->type, tmp->start);
		ft_putstr(tmp->type);
		ft_putstr(" : 0x");
		ft_putendl(ft_utoa_base((uintmax_t)&tmp->start, 16, 'a' + 23)); //A faire à la mano
		while(tmp->alloc)
		{
			// ft_printf("%p - %p : %zu octets\n", tmp->alloc->start, tmp->alloc->start + tmp->alloc->length, tmp->alloc->length);
			ft_putstr("0x");
			ft_putstr(ft_utoa_base((uintmax_t)&tmp->alloc->start, 16, 'a' + 23)); //A faire à la mano
			ft_putstr(" - 0x");
			ft_putstr(ft_utoa_base((uintmax_t)(&tmp->alloc->start + tmp->alloc->length), 16, 'a' + 23)); //A faire à la mano
			ft_putstr(" : ");
			ft_putnbr(tmp->alloc->length);
			ft_putstr(" octet");
			if (tmp->alloc->length != 1)
				ft_putchar('s');
			ft_putendl("");
			size += tmp->alloc->length;
			tmp->alloc = tmp->alloc->next;
		}
		tmp = tmp->next;
	}
	// ft_printf("Total : %zu octets\n", size);
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putstr(" octet");
	if (size != 1)
		ft_putchar('s');
	ft_putendl("");
}
