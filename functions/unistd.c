#include <unistd.h>
#include <stdio.h>
#include <wait.h>
// int access(const char *path, int amode)

int	main()
{
	char	cwd[256];

	if (chdir("/tmp") != 0)
		perror("chdir() error()");
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error()");
		else
			printf("Current working directory is: %s\n", cwd);
	}
}
