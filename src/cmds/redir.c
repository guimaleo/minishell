#include "../inc/minishell.h"

void	check_redir(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("%s\n", cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
}