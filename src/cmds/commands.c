#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	t_cmd	*init;

	init = ft_calloc(sizeof(t_cmd), 1);
	init->args = args;
	init->in = -1;
	init->out = -1;
	if (!terminal()->env)
		init->path = MIN_PATH;//IF UNSET PATH = NULL; && FREE
	else
		{
			init->path = getenv("PATH");
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
	//int		i;
	//char	*tmp;
	pid_t	pid;

	printf("PATH=%s\n", cmd->path);
	check_builtin(cmd);
	if (cmd->next)
		pipex(cmd);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			while (cmd)
			{
				check_acess(cmd);
				cmd = cmd->next;
			}
		}
		else
			wait(NULL);
	}
	free_list(&cmd);
}
