/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pututoabase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 00:37:23 by amineau           #+#    #+#             */
/*   Updated: 2017/09/10 17:07:03 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int			nbrdigit(uintmax_t nbr, int base)
{
	int	pow;

	pow = 0;
	while (nbr / base != 0)
	{
		nbr = nbr / base;
		pow++;
	}
	return (pow + 1);
}

static uintmax_t	ft_power(int nbr, int base)
{
	int			i;
	uintmax_t	res;

	i = 0;
	res = 1;
	while (i++ < nbr)
		res *= base;
	return (res);
}

void				ft_pututoabase(uintmax_t value, int base, char c)
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

int					ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t				ft_atounsi(const char *str)
{
	int		i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	while (ft_isdigit(str[i]))
		nb = nb * 10 + str[i++] - 48;
	return (nb);
}
