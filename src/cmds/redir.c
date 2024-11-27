#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	static t_redirect init;

	init.in = -1;
	return (&init);
}

void	clean_redir(t_redirect *redir)
{
	t_redirect *tmp;

	tmp = redir;
	while (tmp)
	{
		redir = redir->next;
		free(tmp->file);
		free(redir);
		tmp = redir;
	}
}
	int	open_redir(t_cmd *cmd, int *fd_in)
{
	t_redirect *tmp;
	int	fd;
	tmp = cmd->redir;
	fd = 0;
	while (tmp)
	{
		if (*fd_in != 0)
			close(*fd_in);
		if (tmp->in == 1)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
			{
				printf("Can't open file or directory %s\n", tmp->file);
				return (0);
			}
			else
				*fd_in = fd;
		}
		tmp = tmp->next;
	}
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
		printf("CMD:%s\n", cmd->args[i]);
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