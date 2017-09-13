#include "../includes/malloc.h"
#include <string.h>

int main() 
{ 
	pthread_t thread_store[20];
	int i;
	int size;
	int ret;

	for (i = 0; i < 20; i++)
	{
		size = i * 64; 
		ret = pthread_create (
		& thread_store [i], NULL,
			(void*)malloc, (void*)size
		);
	}
	for (i = 0; i < 20; i++)
		pthread_join (thread_store [i], NULL);

	show_alloc_mem();
	return(0);
} 