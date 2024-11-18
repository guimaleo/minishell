#include "../inc/minishell.h"


void	free_redirect(t_redirect *redir)
{
	t_redirect *tmp;
	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = NULL;
		redir = tmp;
	}
}

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	

	while (cmd)
	{
		tmp = cmd->next;
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		if (cmd->redir)
			free_redirect(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
	if (i)
	{
		//if (terminal()->env)
		//	free_doubles((void**)terminal()->env);
		free(terminal()->cwd);
		exit(0);
	}
}

void	args_exit(t_cmd *cmd)
{
	int	ret;
	int	i;
	char *c;

	c = DIGITS;
	i = 0;
	while (c[i])
	{
		if (ft_strcmp(cmd->args[1], c))
		{
			printf(EXIT_ERR);
			clean_exit(cmd, 0);
			exit(2);
		}
		i++;
	}
	ret = ft_atoi(cmd->args[1]);
	printf("%i\n", ret);
	clean_exit(cmd, 0);
	exit(ret);
}
