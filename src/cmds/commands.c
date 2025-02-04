/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:02:14 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 22:39:48 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char **args)
{
	static t_cmd	*init;

	init = ft_calloc(sizeof(t_cmd), 1);
	init->args = args;
	init->in = -1;
	init->out = -1;
	init->path = ft_getenv("PATH");
	init->env = terminal()->env;
	init->abs_build = ft_split(init->path, ':');
	return (init);
}

void	exeggutor(t_cmd *cmd)
{
	expansions(terminal()->cmd);
	quote_analysis(terminal()->cmd);
	check_here(cmd);
	if (cmd->args[0])
		pipex(cmd);
	clean_exit(terminal()->cmd, 0);
}
