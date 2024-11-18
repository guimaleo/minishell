#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	static t_cmd	*init;

	init = ft_calloc(sizeof(t_cmd), 1);
	init->args = args;
	init->in = -1;
	init->out = -1;
	if (!terminal()->env)
		init->path = MIN_PATH;//IF UNSET PATH = NULL; && FREE
	else
		{
			init->path = getenv("PATH");
			//printf("%s\n", getenv("PATH"));
			init->env = terminal()->env;
		}
	init->abs_build = ft_split(init->path, ':');
	if (!init->abs_build)
		perror("Split cmd struct error\n");
	
	return (init);
}

char	*abs_path(char *arg, char *path)
{
	return(ft_strjoin(path, arg));
}

void	exeggutor(t_cmd *cmd)
{
	pid_t	pid;

	pid = -1;
	if (!cmd->next)
	{
		if (!check_builtin(cmd))
		{
			pid = fork();
			if (pid == 0)
			{
				if(!pipex(cmd))
					return ;
			}
			else
				wait(NULL);
		}
	}
	else
	{
		if (!check_builtin(cmd))
			pid = fork();
		if (pid == 0)
		{
			while (cmd)
			{
				if (!pipex(cmd))
					return ;
				cmd = cmd->next;
			}
		}
		else
			wait(NULL);
	}
	clean_exit(terminal()->cmd, 0);
}
