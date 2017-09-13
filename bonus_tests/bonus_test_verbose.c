#include "../includes/malloc.h"

void handler()
{
	char	*addr;

	addr = malloc(1024);
	addr[0] = 42;
	free((void*)addr + 1);
	realloc((void*)addr + 1, 18);
	malloc(1000000000000000);	
}

int main() 
{ 
	char	*addr;

	write(1, "--- Before setenv ---\n", 22);
	handler();

	setenv("MallocVerbose", "1", 0);

	write(1, "\n--- After setenv ---\n", 22);
	handler();
	return(0);
} 