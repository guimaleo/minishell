/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:31:32 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 19:14:19 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_acess(t_cmd *cmd)
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
			printf("HERE!\n");
			tmp = ft_strjoin_char(cmd->abs_build[i], cmd->args[0]);
			if (!access(tmp, F_OK))
				execve(tmp, cmd->args, terminal()->env);
			free(tmp);
			i++;
		}
	}
	printf(CMD"%s\n", cmd->args[0]);
	terminal()->stat = 127;
	clean_exit(terminal()->cmd, 1);
}
void	child_process(t_cmd *cmd, int *fd, int *fd_in)
{
    int	tmp;

    tmp = -1;
    (void)fd_in;
    dup2(*fd_in, STDIN_FILENO);
    tmp = open_redout(cmd);
    printf("IN%d\nOUT%d\n", *fd_in, tmp);
    if (cmd->next)
    {
        if (tmp != -1)
            dup2(tmp, STDOUT_FILENO);
        else
            dup2(fd[1], STDOUT_FILENO);
    }
    else if (tmp != -1)
    {
        fd[1] = tmp;
        dup2(fd[1], STDOUT_FILENO);
    }
    ft_close(fd[0]);
    ft_close(fd[1]);
    check_acess(cmd);
    clean_exit(cmd, 1);
}

void	parent_process(int *fd, int *fd_in, t_cmd *cmd)
{
    wait_children(&terminal()->stat);
    ft_close(fd[1]);
    if (*fd_in > 0)
        ft_close(*fd_in);
    if (cmd->in > 0 && cmd->in != -1)
        ft_close(cmd->in);
    *fd_in = fd[0];
}

int	pipex(t_cmd *cmd)
{
    int		fd[2];
    pid_t	pid;
    int		fd_in = 0;

    while (cmd)
    {
        if ((open_redir(cmd, &fd_in)))
        {
            if (cmd->next || !check_builtin(cmd))
            {
                if (pipe(fd) == -1)
                {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
                pid = fork();
                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                if (pid == 0)
                {
                    ft_close(fd[0]); // Close the read end of the pipe in the child process
                    child_process(cmd, fd, &fd_in);
                }
                else
                {
                    ft_close(fd[1]); // Close the write end of the pipe in the parent process
                    parent_process(fd, &fd_in, cmd);
                }
            }
        }
        cmd = cmd->next;
    }
    if (fd_in != 0)
        ft_close(fd_in);
    return (1);
}
