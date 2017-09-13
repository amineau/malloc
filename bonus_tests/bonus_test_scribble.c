#include "../includes/malloc.h"


void handler()
{
	unsigned char	*addr;

	addr = malloc(1024);

	write(1, "init addr[0] : 0x", 17);
	ft_pututoabase(addr[0], 16, 'A');
	write(1, "\n", 1);

	addr[0] = 42;

	write(1, "set addr[0] : 0x", 16);
	ft_pututoabase(addr[0], 16, 'A');
	write(1, "\n", 1);

	free((void*)addr);

	write(1, "free addr[0] : 0x", 17);
	ft_pututoabase(addr[0], 16, 'A');
	write(1, "\n", 1);
}

int main() 
{ 
	char	*addr;

	write(1, "--- Before setenv ---\n", 22);
	handler();

	setenv("MallocPreScribble", "1", 0);
	setenv("MallocScribble", "1", 0);

	write(1, "\n--- After setenv ---\n", 22);
	handler();
	return(0);
} 