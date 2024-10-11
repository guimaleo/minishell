#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	int	ret;

	if (ac == 1)
		exit(EXIT_FAILURE);
	ret = execve("/bin/ls", av, env);
	printf("%i\n", ret);
}
