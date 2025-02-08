/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:37:05 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 22:18:47 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_redout(t_cmd *cmd)
{
	t_redirect	*tmp;
	int			fd;

	tmp = cmd->redir;
	fd = -1;
	while (tmp)
	{
		if (fd != -1 && tmp->flag < 3)
			ft_close(fd);
		if (tmp->flag == 1)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->flag == 2)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1 && tmp->flag < 3)
		{
			printf("Can't create file %s\n", tmp->file);
			return (-1);
		}
		tmp = tmp->next;
	}
	cmd->out = fd;
	return (fd);
}

void	clear_argso(char **args)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")
			|| !ft_strcmp(args[i], "<"))
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

// void	check_redout(t_cmd *cmd)
// {
// 	int			i;
// 	t_redirect	*tmp;

// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		if (!ft_strcmp(cmd->args[i], ">"))
// 		{
// 			if (!cmd->redir)
// 			{
// 				cmd->redir = init_redir();
// 				if (cmd->args[i + 1])
// 				{
// 					cmd->redir->in = 0;
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
// 					tmp->next->in = 0;
// 					tmp->next->file = ft_strdup(cmd->args[i + 1]);
// 					i += 1;
// 					tmp = tmp->next;
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	clear_argso(cmd->args);
// }
