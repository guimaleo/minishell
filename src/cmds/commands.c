#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	static t_cmd	*init;

	init = ft_calloc(sizeof(t_cmd), 1);
	init->args = args;
	init->in = -1;
	init->out = -1;
	init->path = ft_getenv("PATH");
	init->env = terminal()->env;
	init->abs_build = ft_split(init->path, ':');
	return (init);
}

void	exeggutor(t_cmd *cmd)
{
	//pid_t	pid;

	expansions(terminal()->cmd);
	quote_analysis(terminal()->cmd);
	//check_here(terminal()->cmd);
	//pid = -1;
	pipex(cmd);
	clean_exit(terminal()->cmd, 0);
}
