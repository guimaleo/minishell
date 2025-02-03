#include "minishell.h"

void	here_doc(t_cmd *cmd, char *del)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		ft_close(fd[0]);
		while (1)
		{
			terminal()->input = readline(terminal()->prompt);
			if (!terminal()->input || !ft_strcmp(terminal()->input, del))
			{
				free(terminal()->input);
				break ;
			}
			write(fd[1], terminal()->input, ft_strlen(terminal()->input));
			write(fd[1], "\n", 1);
			free(terminal()->input);
		}
		ft_close(fd[1]);
		exit(terminal()->stat);
	}
	else
	{
		ft_close(fd[1]);
		waitpid(pid, NULL, 0);
		printf("HERE\n");
		cmd->in = fd[0];
	}
}

void	check_here(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (!ft_strncmp(cmd->args[i], "<<", 2))
		{
			terminal()->prompt = "heredoc> ";
			here_doc(cmd, cmd->args[i + 1]);
			free(cmd->args[i]);
			free(cmd->args[i + 1]);
			cmd->args[i] = NULL;
			break ;
		}
		i++;
	}
}
