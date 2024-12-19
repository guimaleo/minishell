/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:34:52 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 18:59:14 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cat < README.md > 2
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
		free(cmd);
		cmd = tmp;
	}
	free(terminal()->input);
	terminal()->input = NULL;
	if (i)
	{
		if (i == 2)
			printf("exit\n");
		free_prealloc();
		exit(terminal()->stat);
	}
}

void	args_exit(t_cmd *cmd)
{
	int	ret;
	int	i;

	i = 0;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			printf(EXIT_ERR);
			clean_exit(cmd, 0);
			exit(2);
		}
		i++;
	}
	ret = ft_atoi(cmd->args[1]);
	printf("%i\n", ret);
	clean_exit(cmd, 0);
	exit(ret);
}
