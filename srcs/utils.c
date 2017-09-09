/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 00:37:23 by amineau           #+#    #+#             */
/*   Updated: 2017/09/09 23:51:22 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*tmp1;
	const char	*tmp2;

	if (!src)
		return (NULL);
	i = 0;
	tmp1 = dst;
	tmp2 = src;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		i++;
	}
	return (dst);
}

void				*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	if (!b || !c)
		return (NULL);
	i = 0;
	tmp = (unsigned char*)b;
	while (i < len)
		tmp[i++] = c;
	return ((unsigned char*)b);
}

void				ft_putunsi(size_t n)
{
	if (n >= 10)
	{
		ft_putunsi(n / 10);
		ft_putunsi(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void				ft_putchar(char c)
{
	write(1, &c, 1);
}

void				ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	write(1, &s[0], i);
}
