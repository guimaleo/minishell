#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	t_redirect *init;

	init = (t_redirect *)ft_calloc(sizeof(t_redirect), 1);
	init->in = -1;
	return (init);
}

int	open_redir(t_cmd *cmd, int *fd_in)
{
	
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
