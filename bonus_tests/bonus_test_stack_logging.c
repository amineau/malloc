#include "../includes/malloc.h"

int main() 
{ 
	char	*addr;

	setenv("MallocStackLogging", "1", 0);
	malloc(1024);
	malloc(1);
	show_alloc_mem();
	return(0);
} 