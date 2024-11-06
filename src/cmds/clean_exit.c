#include "../inc/minishell.h"

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	while (cmd)
	{
		tmp = cmd->next;	
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		//free(cmd->path);
		//free_doubles((void **)cmd->env);
		free(cmd);
		cmd = tmp;
	}
	if (i)
		exit(0);
}