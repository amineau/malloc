/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:27:29 by amineau           #+#    #+#             */
/*   Updated: 2017/09/27 00:30:58 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY (unsigned int)getpagesize() * 27
# define SMALL (unsigned int)getpagesize() * 108

# define BLOCK_STRUCT_SIZE sizeof(t_block)
# define ZONE_STRUCT_SIZE sizeof(t_zone)

# define MALLOC_VERBOSE ft_getenv("MallocVerbose")
# define MALLOC_SCRIBBLE ft_getenv("MallocScribble")
# define MALLOC_PRE_SCRIBBLE ft_getenv("MallocPreScribble")
# define MALLOC_STACK_LOGGING ft_getenv("MallocStackLogging")
# define MALLOC_GUARD_EDGES ft_atounsi(ft_getenv("MallocGuardEdges"))
# define MALLOC_DO_NOT_PROTECT_PRE_LUDE ft_getenv("MallocDoNotProtectPreLude")
# define MALLOC_DO_NOT_PROTECT_POST_LUDE ft_getenv("MallocDoNotProtectPostLude")

# define SIZE_BUFFER_STACK 5
# define DATA_SCRIBBLE 0x55
# define DATA_PRE_SCRIBBLE 0xAA

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <execinfo.h>
# include <pthread.h>

typedef struct	s_block
{
	void			*data;
	size_t			size;
	void			*buffer_stack[SIZE_BUFFER_STACK];
	int				nbr_ret;
}				t_block;

typedef struct	s_zone
{
	size_t			size;
	void			*data;
	t_block			*block;
	struct s_zone	*next;
}				t_zone;

t_zone					**g_zone;
static pthread_mutex_t	g_mutex_stock = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();
void			*malloc_no_lock(size_t size);
void			free_no_lock(void *ptr);
size_t			size_of_data(size_t type);
int				is_large (size_t type);
size_t			get_init_size(size_t size);
t_zone			*find_zone(void *ptr);
void			*init_page(size_t size);
void			*init_zone(void);
t_zone			*create_zone(size_t size);
void			add_zone(t_zone *zone);
size_t			type_zone(size_t size);
t_zone			*find_zone(void *ptr);
t_block			*create_block(void *addr, int flag);
void			init_block(t_block **addr_block, size_t size);
t_block			*block_available(size_t type);
t_block			*find_block(void *ptr, t_zone *zone);
void			ft_putstr(char const *str);
void			ft_putchar(char c);
void			ft_pututoabase(uint64_t value, int base, char c);
size_t			ft_atounsi(const char *str);
void			ft_putunsi(size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);
const char		*ft_getenv(const char *var_env);
void			is_not_allocated(void *ptr, const char *function_name);
void			insufficient_memory();

#endif
