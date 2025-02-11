/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:59:36 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/11 19:38:06 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_f(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd)
		printf("%s\n", cwd);
	free(cwd);
	return ;
}

void	replace_n_erase(t_cmd *cmd, char *input, size_t len)
{
	int		i;
	char	*swap;
	char	*tmp;

	swap = NULL;
	i = 0;
	while (cmd->env[i] && ft_strncmp(cmd->env[i], input, len))
		i++;
	tmp = cmd->env[i];
	while (cmd->env[i])
	{
		swap = cmd->env[i + 1];
		if (swap == NULL)
		{
			cmd->env[i] = NULL;
			break ;
		}
		cmd->env[i] = swap;
		i++;
	}
	free(tmp);
}

void	unset_f(t_cmd *cmd)
{
	int		i;
	bool	flag;
	size_t	len;
	char	*to_unset;

	flag = false;
	to_unset = ft_strdup(cmd->args[1]);
	if (!to_unset)
		return ;
	len = ft_strlen(to_unset);
	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], to_unset, len))
			flag = true;
		i++;
	}
	if (flag)
		replace_n_erase(cmd, to_unset, len);
	free(to_unset);
}

void	redir_aux(t_cmd *cmd)
{
	if (cmd->in > 2)
	{
		if (dup2(cmd->in, STDIN_FILENO) == -1)
			printerror(cmd, "dup2");
	}
	if (cmd->out > 2)
	{
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
			printerror(cmd, "dup2");
	}
}

void	builtin_redir(t_cmd *cmd, t_builtin_func f)
{
	int	pid;

	if (!cmd->next)
	{
		open_redout(cmd);
		open_redir(cmd, &cmd->in);
		pid = fork();
		if (pid == -1)
			return (printerror(cmd, "fork"));
		if (pid == 0)
		{
			redir_aux(cmd);
			if (f)
				f(cmd);
			ft_close(cmd->in);
			ft_close(cmd->out);
			clean_exit(terminal()->cmd, 1);
		}
		else
			waitpid(pid, &terminal()->stat, 0);
		ft_close(cmd->out);
		ft_close(cmd->in);
	}
	else
		f(cmd);
}
