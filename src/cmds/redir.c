#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	t_redirect *init;

	init = (t_redirect *)ft_calloc(sizeof(t_redirect), 1);
	init->in = -1;
	return (init);
}

void	clean_redir(t_redirect *redir)
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
	int	open_redir(t_cmd *cmd, int *fd_in)
{
	t_redirect *tmp;
	int	fd;
	tmp = cmd->redir;
	fd = 0;
	while (tmp)
	{
		printf("REDIR:%s\n", tmp->file);
		tmp = tmp->next;
	}
	tmp = cmd->redir;
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
				terminal()->stat = 126;
				return (0);
			}
			else
			{
				cmd->in = fd;
				*fd_in = fd;
			}
		}
		printf("File:%s   fd:%d\n", tmp->file, fd);
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
	t_redirect *tmp;

	i = 0;
	if (!cmd->redir)
	{
		while(cmd->args[i])
		{
			
			if (!ft_strcmp(cmd->args[i], "<"))
			{
				if (!cmd->redir)
				{
					cmd->redir = init_redir();
					if (cmd->args[i + 1])
					{
						cmd->redir->in = 1;
						cmd->redir->file = ft_strdup(cmd->args[i + 1]);
						i += 1;
						tmp = cmd->redir;
					}
				}
				else
				{
					tmp->next = init_redir();
					if (cmd->args[i + 1])
					{
						tmp->next->in = 1;
						tmp->next->file = ft_strdup(cmd->args[i + 1]);
						i += 1;
						tmp = tmp->next;
					}
				}
			}
			i++;
		}
	 clear_args(cmd->args);
	}
}
