/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:27:29 by amineau           #+#    #+#             */
/*   Updated: 2017/09/04 18:19:43 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>

# include <assert.h>
# include <errno.h>

# include <stdio.h>

# define TINY (unsigned int)getpagesize() * 10
# define SMALL (unsigned int)getpagesize() * 1000


typedef struct 	s_block
{
	void			*data;
	size_t			size;
	int				free;
	struct s_block	*next;
}				t_block;

typedef struct 	s_zone
{
	size_t			size;
	void			*data;	
	t_block 		*block;
 	struct s_zone	*next;
}				t_zone;

# define BLOCK_STRUCT_SIZE sizeof(t_block)
# define ZONE_STRUCT_SIZE sizeof(t_zone)

extern t_zone 	**g_zone;

//void		show_alloc_mem();

//void		ft_putstr(char *str);


#endif
