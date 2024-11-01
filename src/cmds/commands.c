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
		init->path = getenv("PATH");
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
	int		i;
	char	*tmp;
	pid_t	pid;

	printf("PATH=%s\n", cmd->path);
	pid = fork();
	if (pid == 0)
	{
		while (cmd)
		{
			i = 0;
			while (cmd->abs_build[i])
			{
				//split path
				//args + flags
				printf("Arg to be executed: %s\n", cmd->args[0]);
				// tmp = abs_path(cmd);
				i++;
				/*construir as possibilidades de PATH para o execve, chamar num loop, executar*/
				/*execve("PATH, ARGS + FLAGS, ENVP")*/
				tmp = ft_strjoin_char(cmd->abs_build[i], cmd->args[0]);
				printf("tmp: %s\n", tmp);
				printf("abs_build: %s\n", cmd->abs_build[i]);
				execve(tmp, cmd->args, NULL);
				// execve(tmp, cmd->args, NULL);
				free(tmp);
			}
			cmd = cmd->next;
		}
	}
	else
		wait(NULL);
	free_list(&cmd);
}
