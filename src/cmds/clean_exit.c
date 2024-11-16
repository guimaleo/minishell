#include "../inc/minishell.h"

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;

	printf("HERE\n");
	while (cmd)
	{
		tmp = cmd->next;	
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		//free(cmd->path);
		//free_doubles((void **)cmd->env);
		free(cmd);
		//free(terminal()->cwd);
		cmd = tmp;
	}
	if (i)
	{
		//if (terminal()->env)
		//	free_doubles((void**)terminal()->env);
		exit(0);
	}
}