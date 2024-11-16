#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	static t_redirect init;

	init.in = -1;
	return (&init);
}


void	check_redir(char *str)
{
	int	i;
	//int	start;
	//int	len;
	i = 0;
	printf("str:%s\n", str);
	while (str[i])
	{
		while (str[i] != '')
	}
}