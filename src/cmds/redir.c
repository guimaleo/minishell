/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:34:05 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 19:51:30 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redirect	*init_redir(void)
{
	t_redirect	*init;

	init = (t_redirect *)ft_calloc(sizeof(t_redirect), 1);
	return (init);
}

void	clean_redir(t_redirect *redir)
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

int	open_redir(t_cmd *cmd, int *fd_in)
{
	t_redirect	*tmp;
	int			fd;

	tmp = cmd->redir;
	fd = -1;
	while (tmp)
	{
		if (tmp->flag == 3)
		{
			ft_close(cmd->in);
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
			{
				printf("Can't open file or directory %s\n", tmp->file);
				return ((terminal()->stat = 126), 0);
			}
			else
			{
				cmd->in = fd;
				*fd_in = fd;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

void	clear_args(char **args)
{
	int	i;
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

void	redir_out(t_cmd *cmd, char *str, int flag)
{
	t_redirect	*tmp;

	tmp = cmd->redir;
	if (!tmp)
	{
		cmd->redir = init_redir();
		cmd->redir->file = ft_strdup(str);
		cmd->redir->flag = flag;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_redir();
		tmp->next->file = ft_strdup(str);
		tmp->next->next = NULL;
		tmp->next->flag = flag;
	}
}

void	check_redir(t_cmd *cmd)
{
	int			i;
	int			flag;
	redir_func	f;

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
