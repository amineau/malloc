/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 00:37:23 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 00:45:42 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	        nbrdigit(uintmax_t nbr, int base)
{
    int pow;

    pow = 0;
    while (nbr / base != 0)
    {
        nbr = nbr / base;
        pow++;
    }
    return (pow + 1);
}

static uintmax_t    ft_power(int nbr, int base)
{
	int			i;
	uintmax_t	res;

	i = 0;
	res = 1;
	while (i++ < nbr)
		res *= base;
	return (res);
}

void	            ft_putunsi(size_t n)
{
	if (n >= 10)
	{
		ft_putunsi(n / 10);
		ft_putunsi(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void	            ft_putchar(char c)
{
	write(1, &c, 1);
}

void	            ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
        while (s[i])
            i++;
    write(1, &s[0], i);
}

void                ft_pututoabase(uintmax_t value, int base, char c)
{
	int		pow;
	int		digit;

	pow = nbrdigit(value, base);
	while (--pow >= 0)
	{
		digit = value / ft_power(pow, base);
		value %= ft_power(pow, base);
		if (digit < 10)
			ft_putchar(digit + 48);
		else
			ft_putchar(digit + c - 33);
	}
}