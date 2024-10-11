#include <unistd.h>
#include <stdio.h>

// int access(const char *path, int amode)

int	main()
{
	pid_t	pid;

	printf("Fork wait for child call\n\n");
	pid = fork();
	if (pid != 0) // If it's not the child
	{
		wait(NULL);
		printf("I've been waiting my child!\n");
	}
	else
		printf("Parent process will wait for me!\n");
}
