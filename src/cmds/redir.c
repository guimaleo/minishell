#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	static t_redirect init;

	init.in = -1;
	return (&init);
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