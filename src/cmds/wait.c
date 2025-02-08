/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:29:24 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 22:37:25 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_redir(t_cmd *cmd)
{
	int				i;
	int				flag;
	t_redir_func	f;

	i = 1;
	flag = 0;
	while (cmd->args[i])
	{
		f = NULL;
		if (!ft_strcmp(cmd->args[i], ">") && cmd->args[i + 1])
			flag = 1;
		else if (!ft_strcmp(cmd->args[i], ">>") && cmd->args[i + 1])
			flag = 2;
		else if (!ft_strcmp(cmd->args[i], "<") && cmd->args[i + 1])
			flag = 3;
		if (flag)
			f = redir_out;
		if (f)
		{
			f(cmd, cmd->args[i + 1], flag);
		}
		flag = 0;
		i++;
	}
	clear_argso(cmd->args);
}

void	wait_children(int *all_stat)
{
	int		wstat;
	pid_t	pid;

	while (1)
	{
		pid = wait(&wstat);
		if (pid == -1)
		{
			if (errno == EINTR)
			{
				terminal()->stat = 128 + terminal()->sig;
				break ;
			}
		}
		if (WIFEXITED(wstat))
		{
			terminal()->stat = WEXITSTATUS(wstat);
			(void)all_stat;
			break ;
		}
	}
}

void	check_acess(t_cmd *cmd, int fd_in)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!check_builtin(cmd))
	{
		if (!access(cmd->args[0], F_OK))
			execve(cmd->args[0], cmd->args, terminal()->env);
		while (cmd->abs_build && cmd->abs_build[i])
		{
			tmp = ft_strjoin_char(cmd->abs_build[i], cmd->args[0]);
			if (!access(tmp, F_OK))
				execve(tmp, cmd->args, terminal()->env);
			free(tmp);
			i++;
		}
	}
	printf(CMD"%s\n", cmd->args[0]);
	if (fd_in > 2)
		close(fd_in);
	close(0);
	terminal()->stat = 127;
	clean_exit(terminal()->cmd, 1);
}
