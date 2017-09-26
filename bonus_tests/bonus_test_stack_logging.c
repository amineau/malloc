#include "../includes/malloc.h"

int main() 
{ 
	char	*addr;

	setenv("MallocStackLogging", "1", 0);
	addr = malloc(1024);
	addr = malloc(1);
	show_alloc_mem();
	return(0);
} 
