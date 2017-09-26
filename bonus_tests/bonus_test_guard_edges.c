#include "../includes/malloc.h"


void handler()
{
	unsigned char	*addr;

	addr = malloc(406600);
	show_alloc_mem();
	free((void*)addr);
}

int main() 
{ 
	char	*addr;

	write(1, "--- Before setenv ---\n", 22);
	handler();

	setenv("MallocGuardEdges", "1024", 0);

	write(1, "\n--- After setenv ---\n", 22);
	handler();
	return(0);
} 