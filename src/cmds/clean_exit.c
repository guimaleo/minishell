#include "../inc/minishell.h"

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;

	
	while (cmd)
	{
		tmp = cmd->next;	
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		if (cmd->redir)
			clean_redir(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
	free(terminal()->input);
	terminal()->input = NULL;
	if (i)
	{
		//if (terminal()->env)
		//	free_doubles((void**)terminal()->env);
		exit(0);
	}
}