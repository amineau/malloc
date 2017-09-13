/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 21:01:50 by amineau           #+#    #+#             */
/*   Updated: 2017/09/14 00:49:32 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	is_not_allocated(void *ptr, const char *function_name)
{
	if (MALLOC_VERBOSE)
	{
		ft_putstr("*** error for object 0x");
		ft_pututoabase((uint64_t)ptr, 16, 'a');
		ft_putstr(": pointer being ");
		ft_putstr(function_name);
		ft_putstr(" was not allocated\n");
	}
}

void	insufficient_memory(void)
{
	if (MALLOC_VERBOSE)
		ft_putstr("*** error: can't allocate region\n");
}
