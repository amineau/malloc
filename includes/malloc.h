/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:27:29 by amineau           #+#    #+#             */
/*   Updated: 2016/12/26 19:27:23 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include "libft.h"
# include "ft_printf.h"
# include <sys/mman.h>

# define TINY (unsigned int)getpagesize() * 1
# define SMALL (unsigned int)getpagesize() * 10


typedef struct 	s_alloc
{
	void			*start;
	size_t			length;
	struct s_alloc 	*next;
}				t_alloc;

typedef struct 	s_zone
{
	char					*type;
	void					*start;
	t_alloc				*current;
	t_alloc 			*alloc;
 	struct s_zone	*next;
}				t_zone;

extern t_zone 	*g_zone;

// void		ft_free(void *ptr);
void 		*ft_malloc(size_t size);
void 		*ft_realloc(void *ptr, size_t size);
void		show_alloc_mem();


t_zone	*zone_create(size_t size, char *type);
void		zone_insert(t_zone *zone);
char		*type_zone(size_t type);
size_t	length_zone(size_t size);

#endif
