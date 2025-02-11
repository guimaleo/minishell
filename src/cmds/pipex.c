/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:31:32 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 22:38:20 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_process(t_cmd *cmd, int *fd, int *fd_in)
{
	int	tmp;

	tmp = -1;
	if (cmd->heredoc != 0)
		*fd_in = cmd->heredoc;
	dup2(*fd_in, STDIN_FILENO);
	tmp = open_redout(cmd);
	if (cmd->next)
	{
		if (tmp != -1)
			dup2(tmp, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else if (tmp != -1)
		dup2(tmp, STDOUT_FILENO);
	ft_close(fd[0]);
	if (tmp == -1)
		ft_close(fd[1]);
	else
		ft_close(tmp);
	check_acess(cmd, *fd_in);
	ft_close(fd[0]);
	ft_close(fd[1]);
	clean_exit(cmd, 1);
}

void	parent_process(int *fd, int *fd_in, t_cmd *cmd)
{
	wait_children(&terminal()->stat);
	ft_close(fd[1]);
	ft_close(*fd_in);
	ft_close(cmd->in);
	*fd_in = fd[0];
}

void	error_handle(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_pipeaux(int *fd, int *fd_in, t_cmd *cmd, int flag)
{
	if (flag)
	{
		ft_close(fd[0]);
		child_process(cmd, fd, fd_in);
	}
	else
	{
		ft_close(fd[1]);
		parent_process(fd, fd_in, cmd);
	}
}

int	pipex(t_cmd *cmd)
{
	int		fd_in;
	pid_t	pid;

	fd_in = 0;
	while (cmd)
	{
		if ((open_redir(cmd, &fd_in)))
		{
			if (cmd->next || !check_builtin(cmd))
			{
				if (pipe(cmd->fd) == -1)
					error_handle("pipe");
				pid = fork();
				if (pid == -1)
					error_handle("fork");
				if (pid == 0)
					ft_pipeaux(cmd->fd, &fd_in, cmd, 1);
				else
					ft_pipeaux(cmd->fd, &fd_in, cmd, 0);
			}
		}
		cmd = cmd->next;
	}
	return (ft_close(fd_in), 1);
}
