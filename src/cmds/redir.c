#include "../inc/minishell.h"

void	check_redir(t_cmd *cmd)
{
	int	i;
	//int	tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			i++;
		}
		cmd = cmd->next;
	}
}