/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:13:05 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:12 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_completion(t_cmd *cmd, char *tmp)
{
	if (cmd->args[1])
		tmp = cmd->args[1];
	else
		tmp = terminal()->home;
	if (chdir(tmp) == -1)
	{
		printf("%s%s\n", CD_ERR, tmp);
		return ;
	}
	if (terminal()->old_cwd)
		free(terminal()->old_cwd);
	terminal()->old_cwd = ft_strdup(terminal()->cwd);
	if (terminal()->cwd)
		free(terminal()->cwd);
	terminal()->cwd = getcwd(NULL, 0);
	if (!terminal()->cwd)
	{
		printf("%s%s\n", CD_ERR, tmp);
		return ;
	}
}

void	cd_f(t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	cd_completion(cmd, tmp);
	printf("%s\n", terminal()->cwd);
}

void	env_injection(t_cmd *cmd, char *tmp)
{
	int		i;
	char	**new_env;

	i = 0;
	(void)cmd;
	new_env = NULL;
	while (terminal()->env && terminal()->env[i])
		i++;
	if (tmp)
		new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	while (terminal()->env && terminal()->env[i])
	{
		new_env[i] = ft_strdup(terminal()->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(tmp);
	free_doubles((void **)terminal()->env);
	terminal()->env = new_env;
}

void	env_f(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (terminal()->no_env)
	{
		while (terminal()->env[i])
		{
			if (!ft_strcmp(terminal()->env[i], "_=/usr/bin/env"))
				break ;
			i++;
		}
	}
	if (terminal()->no_env && !terminal()->env[i])
		env_injection(cmd, "_=/usr/bin/env");
	cmd->env = terminal()->env;
	i = 0;
	while (terminal()->env[i])
		printf("%s\n", terminal()->env[i++]);
}

void	export_f(t_cmd *cmd)
{
	int		i;
	size_t	len;
	char	*tmp;
	char	**to_exp;

	to_exp = ft_split(cmd->args[1], '=');
	if (!to_exp)
		return ;
	tmp = ft_strdup(cmd->args[1]);
	len = ft_strlen(to_exp[0]);
	i = 0;
	while (cmd->env && cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], to_exp[0], len))
		{
			free(cmd->env[i]);
			cmd->env[i] = tmp;
			free_doubles((void **)to_exp);
			return ;
		}
		i++;
	}
	env_injection(cmd, tmp);
	free(tmp);
	free_doubles((void **)to_exp);
}
