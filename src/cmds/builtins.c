/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:17:35 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/17 23:22:30 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built(t_cmd *cmd)
{
	int			i;
	int			j;
	static char	*tmp[8] = BUILTIN;

	if (!cmd)
		return (-1);
	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		while (tmp[j])
		{
			if (!ft_strcmp(cmd->args[i], tmp[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_builtin(t_cmd *cmd)
{
	int			i;
	int			j;
	int			check;
	static char	*tmp[8] = BUILTIN;

	if (!cmd)
		return (-1);
	i = 0;
	check = 0;
	while (cmd->args[i])
	{
		j = 0;
		while (tmp[j])
		{
			if (!ft_strcmp(cmd->args[i], tmp[j]))
				check = exec_builtin(cmd);
			j++;
		}
		i++;
	}
	return (check);
}

void	echo_f(t_cmd *cmd)
{
	int	flag;
	int	i;

	i = 1;
	flag = (!ft_strncmp(cmd->args[1], "-n", 2));
	i += flag;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i++]);
		if (cmd->args[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}

int	exec_builtin(t_cmd *cmd)
{
	builtin_func	f;

	f = NULL;
	if (!ft_strcmp(cmd->args[0], "cd"))
		f = cd_f;
	else if (!ft_strcmp(cmd->args[0], "echo"))
		f = echo_f;
	else if (!ft_strcmp(cmd->args[0], "env"))
		f = env_f;
	else if (!ft_strcmp(cmd->args[0], "unset"))
		f = unset_f;
	else if (!ft_strcmp(cmd->args[0], "export"))
		f = export_f;
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		f = pwd_f;
	else if (!ft_strcmp(cmd->args[0], "exit") && !cmd->args[1])
		f = built_exit;
	else if (!ft_strcmp(cmd->args[0], "exit") && cmd->args[1])
		args_exit(terminal()->cmd);
	else
		return (0);
	f(cmd);
	return (1);
}

void	replace_n_erase(t_cmd *cmd, char *input, size_t len)
{
	int		i;
	char	*swap;

	swap = NULL;
	i = 0;
	while (cmd->env[i] && ft_strncmp(cmd->env[i], input, len))
		i++;
	while (cmd->env[i])
	{
		swap = cmd->env[i + 1];
		if (swap == NULL)
		{
			cmd->env[i] = NULL;
			break ;
		}
		cmd->env[i] = swap;
		i++;
	}
}

void	unset_f(t_cmd *cmd)
{
	int		i;
	bool	flag;
	size_t	len;
	char	*to_unset;

	flag = false;
	to_unset = ft_strdup(cmd->args[1]);
	if (!to_unset)
		return ;
	len = ft_strlen(to_unset);
	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], to_unset, len))
			flag = true;
		i++;
	}
	if (flag)
		replace_n_erase(cmd, to_unset, len);
	free(to_unset);
}
