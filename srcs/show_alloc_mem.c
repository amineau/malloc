/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:17:38 by amineau           #+#    #+#             */
/*   Updated: 2017/09/10 01:33:26 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone **g_zone;

size_t	show_block(t_block *block)
{
	if (!block->size)
		return (0);
	ft_putstr("0x");
	ft_pututoabase((uintmax_t)block->data, 16, 'a' + 23);
	ft_putstr(" - 0x");
	ft_pututoabase((uintmax_t)(block->data + block->size), 16, 'a' + 23);
	ft_putstr(" : ");
	ft_putunsi(block->size);
	ft_putstr(" octet");
	if (block->size != 1)
		ft_putchar('s');
	ft_putstr("\n");
	return (block->size);
}

void	show_type(size_t type)
{
	if (type == TINY)
		ft_putstr("TINY");
	else if (type == SMALL)
		ft_putstr("SMALL");
	else
		ft_putstr("LARGE");
}

void	show_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putunsi(total);
	ft_putstr(" octet");
	if (total > 1)
		ft_putchar('s');
	ft_putstr("\n");
}

size_t	show_zone(t_zone *zone)
{
	size_t	total;
	t_block	*block;
	size_t	interval;
	int		i;
	int		loop;

	i = 0;
	total = 0;
	block = zone->block;
	interval = size_of_data(zone->size) + BLOCK_STRUCT_SIZE;
	loop = (is_large(zone->size)) ? 1 : 100;
	show_type(zone->size);
	ft_putstr(" : 0x");
	ft_pututoabase((uintmax_t)zone->data, 16, 'a' + 23);
	ft_putstr("\n");
	while (i++ < loop)
	{
		total += show_block(block);
		block = (t_block*)((size_t)block + interval);
	}
	return (total);
}

void	show_alloc_mem(void)
{
	t_zone	*zone;
	size_t	total;

	total = 0;
	if (g_zone)
	{
		zone = *g_zone;
		while (zone)
		{
			total += show_zone(zone);
			zone = zone->next;
		}
	}
	show_total(total);
}
