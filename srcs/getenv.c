/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 23:06:29 by amineau           #+#    #+#             */
/*   Updated: 2017/09/27 00:27:26 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	if (!s2 || s2[0] == '\0')
		return ((char*)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i + j] == s2[j] && s2[j] != '\0')
				j++;
			if (s2[j] == '\0')
				return ((char*)s1 + i + j + 1);
		}
		i++;
	}
	return (NULL);
}

const char	*ft_getenv(const char *var_env)
{
	extern char	**environ;
	char		**tmp;
	char		*str;
;
	tmp = environ;
	str = NULL;
	while (*tmp
		&& !(str = ft_strstr(*tmp++, var_env)))
		;
	return (str);
}
