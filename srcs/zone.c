/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:17:38 by amineau           #+#    #+#             */
/*   Updated: 2016/12/26 13:28:56 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	*type_zone(size_t type)
{
	if (type == TINY)
		return ("TINY");
	if (type == SMALL)
		return ("SMALL");
	return ("LARGE");
}

size_t 	size_zone(char *type)
{
	if (!ft_strcmp(type, "TINY"))
		return (TINY);
	return (SMALL);
}

size_t	length_zone(size_t size)
{
	size_t length;

	length = (size + sizeof(t_alloc)) * 100 + sizeof(t_zone);
	if (length < TINY)
		return (TINY);
	else if (length < SMALL)
		return (SMALL);
	return (size);
}