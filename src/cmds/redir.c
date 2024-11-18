#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	static t_redirect init;

	init.in = -1;
	return (&init);
}

int	open_redir(t_cmd *cmd, int *fd_in)
{
	t_redirect *tmp;
	int	fd;
	tmp = cmd->redir;
	while (tmp)
	{
		if (fd_in != 0)
			close(*fd_in);
		fd = open(tmp->file, O_RDONLY);
		if (fd == -1)
		{
			printf("Can't open%s\n");
			return (0);
		}
		else
			*fd_in = fd;
		tmp = tmp->next;
	}
	printf("%d\n", fd);
	return (1);
}

void	clear_args(char **args)
{
	int i;
	int	start;

	i = 0;
	start = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<"))
		{
			free(args[i]);
			args[i] = NULL;
			if (args[i + 1])
			{
				free(args[i + 1]);
				args[i + 1] = NULL;
				i++;
			}
		}
		else
			args[start++] = args[i];
		i++;
	}
}

void	check_redir(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], "<"))
		{
			cmd->redir = init_redir();
			if (cmd->args[i + 1])
			{
				cmd->redir->file = ft_strdup(cmd->args[i + 1]);
				cmd->redir->in = 1;
			}
		}
		i++;
	}
	cmd = cmd->next;
}