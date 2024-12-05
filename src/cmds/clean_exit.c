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

void	built_exit(t_cmd *cmd)
{
	t_cmd	*tmp;
	
	if (cmd->in != 0 && cmd->in != -1)
		close(cmd->in);
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
	//if (terminal()->env)
	//	free_doubles((void**)terminal()->env);
	free(terminal()->cwd);
	exit(terminal()->stat);
}

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	
	if (cmd->in != 0 && cmd->in != -1)
		close(cmd->in);
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
		free(terminal()->cwd);
		exit(terminal()->stat);
	}
}

void	args_exit(t_cmd *cmd)
{
	int	ret;
	int	i;

	i = 0;
	while (cmd->args[1][i])
	{	
		if (!ft_isdigit(cmd->args[1][i]))
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
