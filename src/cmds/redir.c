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
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->flag == 3)
		{
			ft_close(cmd->in);
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
			{
				printf("Can't open file or directory %s\n", tmp->file);
				terminal()->stat = 126;
				return (0);
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
	t_redirect *tmp;
	printf("oi\n");
	tmp = cmd->redir;
	if (!tmp)
	{
		printf("IF\n");
		cmd->redir = init_redir();
		cmd->redir->file = ft_strdup(str);
		cmd->redir->flag = flag;
	}
	else
	{
		printf("ELSE\n");
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_redir();
		tmp->next->file = ft_strdup(str);
		tmp->next->next = NULL;
		tmp->next->flag = flag;
	}
	// tmp->file = str;
	tmp = cmd->redir;
	while (tmp)
	{
		printf("%s\n", tmp->file);
		tmp = tmp->next;
	}
}


void	check_redir(t_cmd *cmd)
{
	redir_func f;
	int		i;
	int flag;

	i = 1;
	f = NULL;
	flag = 0;
	while (cmd->args[i])
	{
		//printf("ARG1:%s\nARG2:%s\n", cmd->args[i], cmd->args[i+1]);
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
		f = NULL;
		flag = 0;
		i++;
	}
	clear_argso(cmd->args);
	i = 0;
	while (cmd->args[i])
	{
		// printf("%s\n", cmd->args[i]);
		i++;
	}
}
	// int			i;
	// t_redirect	*tmp;

	// i = 0;
	// if (!cmd->redir)
	// {
	// 	while (cmd->args[i])
	// 	{
	// 		if (!ft_strcmp(cmd->args[i], "<"))
	// 		{
	// 			if (!cmd->redir)
	// 			{
	// 				cmd->redir = init_redir();
	// 				if (cmd->args[i + 1])
	// 				{
	// 					cmd->redir->in = 1;
	// 					cmd->redir->file = ft_strdup(cmd->args[i + 1]);
	// 					i += 1;
	// 					tmp = cmd->redir;
	// 				}
	// 			}
	// 			else
	// 			{
	// 				tmp->next = init_redir();
	// 				if (cmd->args[i + 1])
	// 				{
	// 					tmp->next->in = 1;
	// 					tmp->next->file = ft_strdup(cmd->args[i + 1]);
	// 					i += 1;
	// 					tmp = tmp->next;
	// 				}
	// 			}
	// 		}
	// 		i++;
	// 	}
	// 	clear_args(cmd->args);
	// }
// }
