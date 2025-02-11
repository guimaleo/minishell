/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:34:52 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 21:59:32 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redirect(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = NULL;
		redir = tmp;
	}
}

void	built_exit(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd->in != 0 && cmd->in != -1)
		ft_close(cmd->in);
	while (cmd)
	{
		tmp = cmd->next;
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		if (cmd->redir)
			clean_redir(cmd->redir);
		ft_close(cmd->out);
		ft_close(cmd->in);
		free(cmd);
		cmd = tmp;
	}
	free(terminal()->input);
	terminal()->input = NULL;
	free_prealloc();
	printf("exit\n");
	exit(terminal()->stat);
}

void	clean_exit(t_cmd *cmd, int i)
{
	t_cmd	*tmp;

	if (cmd && cmd->in != 0 && cmd->in != -1)
		ft_close(cmd->in);
	while (cmd)
	{
		tmp = cmd->next;
		free_doubles((void **)cmd->args);
		free_doubles((void **)cmd->abs_build);
		if (cmd->redir)
			clean_redir(cmd->redir);
		if (cmd->heredoc != 0)
			close(cmd->heredoc);
		ft_close(cmd->out);
		ft_close(cmd->fd[0]);
		ft_close(cmd->fd[1]);
		free(cmd);
		cmd = tmp;
	}
	terminal()->input = NULL;
	if (i)
	{
		free_prealloc();
		exit(terminal()->stat);
	}
}

void	print_exit(t_cmd *cmd)
{
	printf(EXIT_ERR);
	clean_exit(cmd, 0);
	free_prealloc();
	exit(2);
}

void	args_exit(t_cmd *cmd)
{
	int	ret;
	int	i;

	i = 0;
	if (cmd->args[1][i] == '-' || cmd->args[1][i] == '+' )
		i++;
	if (!cmd->args[1][i])
		print_exit(cmd);
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
			print_exit(cmd);
		i++;
	}
	ret = ft_atoi(cmd->args[1]);
	printf("exit\n");
	clean_exit(cmd, 0);
	free_prealloc();
	exit(ret);
}
