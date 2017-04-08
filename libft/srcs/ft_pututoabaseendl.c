/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pututoabaseendl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 10:48:52 by amineau           #+#    #+#             */
/*   Updated: 2017/04/07 11:29:54 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		    ft_pututoabaseendl(uintmax_t value, int base, char c)
{
	ft_pututoabase(value, base, c);
  ft_putchar('\n');
}
