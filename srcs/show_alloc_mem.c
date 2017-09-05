/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:17:38 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 02:36:20 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone **g_zone;

void	show_alloc_mem()
{
	t_zone	*zone;
	t_block	*block;
	char	*type;
	size_t	interval;
	size_t	size;
	int		i;
	int		loop;

	size = 0;
	if (g_zone)
	{
		//Gros bug ici quand *g_zone est revenu à null
		zone = *g_zone;
		while (zone)
		{
			if (zone->size == TINY)
				type = "TINY";
			else if (zone->size == SMALL)
				type = "SMALL";
			else
				type = "LARGE";
			ft_putstr(type);
			ft_putstr(" : 0x");
			ft_pututoabase((uintmax_t)zone->data, 16, 'a' + 23);
			ft_putstr("\n");
			block = zone->block;
			interval = size_of_data(zone->size) + BLOCK_STRUCT_SIZE;
			i = 0;
			loop = (zone->size > SMALL) ? 1 : 100;			
			while(i++ < loop)
			{
				if (block->size)
				{
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
					size += block->size;
				}
				block = (t_block*)((size_t)block + interval);
			}
			zone = zone->next;
		}
	}
	ft_putstr("Total : ");
	ft_putunsi(size);
	ft_putstr(" octet");
	if (size > 1)
		ft_putchar('s');
	ft_putstr("\n");
}
