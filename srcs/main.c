/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 11:54:02 by amineau           #+#    #+#             */
/*   Updated: 2016/12/26 15:11:41 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int test(char c)
{
	static char	*str;
	int i = 0;
	ft_printf("********\nstr : %s\naddr_before : %#x\n********", str, str);
	str = (char*)mmap(0, TINY, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	while (i < TINY - 1)
		str[i++] = c;
	ft_printf("********\nstr : %s\naddr_after : %#x\nc : %c\n********\n", str, str, c);
	return (0);
}

int main()
{
	int i = 0;
	
	while (i++ < 5)
		test(i + 65);
	ft_printf("%d\n", TINY);
	return (0);
}
