/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:27:29 by amineau           #+#    #+#             */
/*   Updated: 2017/09/10 01:10:51 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY (unsigned int)getpagesize() * 4
# define SMALL (unsigned int)getpagesize() * 26

# define BLOCK_STRUCT_SIZE sizeof(t_block)
# define ZONE_STRUCT_SIZE sizeof(t_zone)

# define LENGTH_BUFFER_STACK 10

# define MALLOC_SCRIBBLE getenv("MALLOC_SCRIBBLE")
# define MALLOC_PRE_SCRIBBLE getenv("MALLOC_PRE_SCRIBBLE")
# define MALLOC_STACK_LOGGING getenv("MALLOC_STACK_LOGGING")


# include <sys/mman.h>
# include <unistd.h>
# include <inttypes.h>
# include <stdlib.h>
# include <execinfo.h>

# include <string.h>

# include <stdio.h>


typedef struct	s_block
{
	void			*data;
	size_t			size;
	int				free;
	void			*buffer_stack[LENGTH_BUFFER_STACK];
	int				nbr_ret;
}				t_block;

typedef struct	s_zone
{
	size_t			size;
	void			*data;
	t_block			*block;
	struct s_zone	*next;
}				t_zone;

extern t_zone	**g_zone;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();
size_t			size_of_data(size_t type);
int				is_large (size_t type);
t_zone			*find_zone(void *ptr);
void			*init_page(size_t size);
void			add_zone(t_zone *zone);
size_t			type_zone(size_t size);
void			ft_putstr(char const *str);
void			ft_putchar(char c);
void			ft_pututoabase(uintmax_t value, int base, char c);
void			ft_putunsi(size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);

#endif
