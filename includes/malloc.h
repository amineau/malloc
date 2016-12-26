/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
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

# define TINY getpagesize()
# define SMALL getpagesize() * 10


typedef struct	s_malloc
{
	void			*start;
	void			*end;
	struct s_malloc	*next;
}				t_malloc;

typedef struct	s_zone_tiny
{
	void				*zone;
	void				*position;
	size_t				max;
	t_malloc			*alloc;
	struct s_zone_tiny	*next;
}				t_zone_tiny;

typedef struct	s_zone_small
{
	void				*zone;
	void				*position;
	size_t				max;
	t_malloc			*alloc;
	struct s_zone_small	*next;
}				t_zone_small;

typedef struct	s_zone_large
{
	void				*zone;
	void				*start;
	void				*end;
	struct s_zone_large	*next;
}				t_zone_large;

typedef struct	s_zone
{
	t_zone_tiny		*tiny;
	t_zone_small	*small;
	t_zone_large	*large;
}				t_zone;

#endif
