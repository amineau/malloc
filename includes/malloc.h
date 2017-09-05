/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:27:29 by amineau           #+#    #+#             */
/*   Updated: 2017/09/05 16:49:53 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>

# include <assert.h>
# include <errno.h>

# include <stdio.h>



typedef struct 	s_block
{
	void			*data;
	size_t			size;
	int				free;
}				t_block;

typedef struct 	s_zone
{
	size_t			size;
	void			*data;	
	t_block 		*block;
	struct s_zone	*next;
}				t_zone;

# define TINY (unsigned int)getpagesize() * 26
# define SMALL (unsigned int)getpagesize() * 2600
# define BLOCK_STRUCT_SIZE sizeof(t_block)
# define ZONE_STRUCT_SIZE sizeof(t_zone)

extern t_zone 	**g_zone;

void		*ft_malloc(size_t size);
void		ft_free(void *ptr);
void		*ft_realloc(void *ptr, size_t size);
void		show_alloc_mem();


size_t		size_of_data(size_t type);
int			is_large (size_t type);
t_zone		*find_zone(void *ptr);
void		*init_page(size_t size);
void		add_zone(t_zone *zone);


void		ft_putstr(char const *str);
void		ft_putchar(char c);
void		ft_pututoabase(uintmax_t value, int base, char c);
void		ft_putunsi(size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);



#endif
