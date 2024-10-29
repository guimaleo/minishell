#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	t_cmd	*init;

	init = ft_calloc(sizeof(t_cmd), 1);
	init->args = args;
	init->in = -1;
	init->out = -1;
	return (init);
}

void	exeggutor(t_cmd *cmd)
{
	int		i;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("Arg to be executed: %s\n", cmd->args[i]);
			i++;
			/*construir as possibilidades de PATH para o execve, chamar num loop, executar*/
			execve("/bin/", (char **)cmd->args[i], NULL);
		}
		cmd = cmd->next;
	}
	free_list(&cmd);
}



