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
# include <sys/mman.h>

# define TINY (unsigned int)getpagesize() * 100
# define SMALL (unsigned int)getpagesize() * 10000


typedef struct 	s_alloc
{
	void			*start;
	size_t			length;
	struct s_alloc 	*next;
}				t_alloc;

typedef struct 	s_zone
{
	short			type;
	void			*start;
	t_alloc 		*alloc;
 	struct s_zone	*next;
}				t_zone;

t_zone 		**get_static();
void		show_alloc_mem(t_zone *zone);

#endif
