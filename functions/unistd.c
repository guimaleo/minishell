#include <unistd.h>
#include <stdio.h>

// int access(const char *path, int amode)

int		main(void)
{
	int		res[3];
	int		i;

	res[0] = access("/bin/ls", 0);	//Returns 0, as right execution
	res[1] = access("ls", 0);		//Without the absolute path returns an error
	res[2] = access("/bin/cd", 0);	//Since the "cd" command doesn't exist in the /bin, returns an error
	for(i = 0; i < 3; i++)
		printf("Access return: %i\n", res[i]);
}

