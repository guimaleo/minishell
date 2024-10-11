#include <unistd.h>
#include <stdio.h>

// int access(const char *path, int amode)

int		main(void)
{
	int		res[3];
	int		i;

	res[0] = access("/bin/ls", 0);
	res[1] = access("ls", 0);
	res[2] = access("/bin/cd", 0);
	for(i = 0; i < 3; i++)
		printf("Access return: %i\n", res[i]);
}

