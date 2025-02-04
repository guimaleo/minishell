/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:02:26 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 22:21:50 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(int fd, char *del)
{
	while (1)
	{
		terminal()->input = readline(terminal()->prompt);
		if (!terminal()->input || !ft_strcmp(terminal()->input, del))
		{
			free(terminal()->input);
			break ;
		}
		write(fd, terminal()->input, ft_strlen(terminal()->input));
		write(fd, "\n", 1);
		free(terminal()->input);
	}
}

void	here_doc(t_cmd *cmd, char *del, t_cmd *head)
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
		loop(fd[1], del);
		ft_close(fd[1]);
		clean_exit(head, 1);
	}
	else
	{
		ft_close(fd[1]);
		waitpid(pid, NULL, 0);
		cmd->heredoc = fd[0];
	}
}

void	check_here(t_cmd *cmd)
{
	int		i;
	t_cmd	*head;

	head = cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			if (!ft_strncmp(cmd->args[i], "<<", 2))
			{
				terminal()->prompt = "heredoc> ";
				here_doc(cmd, cmd->args[i + 1], head);
				free(cmd->args[i]);
				free(cmd->args[i + 1]);
				cmd->args[i] = NULL;
				break ;
			}
			i++;
		}
		cmd = cmd->next;
	}
}
