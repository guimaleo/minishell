/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:17:35 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/11 18:44:33 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**take_bt(void)
{
	static char	*bt[8];

	bt[0] = "cd";
	bt[1] = "echo";
	bt[2] = "exit";
	bt[3] = "export";
	bt[4] = "unset";
	bt[5] = "pwd";
	bt[6] = "env";
	bt[7] = 0;
	return (bt);
}

int	check_built(t_cmd *cmd)
{
	int			i;
	int			j;
	char		**bt;

	if (!cmd)
		return (-1);
	i = 0;
	bt = take_bt();
	while (cmd->args[i])
	{
		j = 0;
		while (bt[j])
		{
			if (!ft_strcmp(cmd->args[i], bt[j]))
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
	char		**tmp;

	tmp = take_bt();
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
void	printerror(t_cmd *cmd, char *s)
{
	perror(s);
	if (!ft_strcmp(s, "fork"))
		return ;
	clean_exit(cmd, 1);
}
void builtin_redir(t_cmd *cmd, t_builtin_func f)
{
	int pid;
	printf("%p\n", cmd->next);
	if (!cmd->next)
	{
		open_redout(cmd);
		open_redir(cmd, &cmd->in);
		printf("%dIN\n%dOUT\n", cmd->in, cmd->out);
		pid = fork();
		if (pid == -1) 
		{
			return (printerror(cmd, "fork"));
		}
		if (pid == 0)
		{
			if (cmd->in > 2)
			{
				if (dup2(cmd->in, STDIN_FILENO) == -1) 
					printerror(cmd, "dup2");
			}
			if (cmd->out > 2) 
			{
				if (dup2(cmd->out, STDOUT_FILENO) == -1) 
					printerror(cmd, "dup2");
			}
			if(f)
				f(cmd);
			ft_close(cmd->in);
			ft_close(cmd->out);
			clean_exit(terminal()->cmd, 1);
		} 
		else 
			waitpid(pid, &terminal()->stat, 0);
		ft_close(cmd->out);
		ft_close(cmd->in);
	}
	else
		f(cmd);
}

int	exec_builtin(t_cmd *cmd)
{
	t_builtin_func	f;

	f = NULL;
	if (!ft_strcmp(cmd->args[0], "cd"))
		f = cd_f;
	else if (!ft_strcmp(cmd->args[0], "echo"))
		f = echo_f;
	else if (!ft_strcmp(cmd->args[0], "env"))
		f = env_f;
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset_f(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export_f(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		f = pwd_f;
	else if (!ft_strcmp(cmd->args[0], "exit") && !cmd->args[1])
		built_exit(terminal()->cmd);
	else if (!ft_strcmp(cmd->args[0], "exit") && cmd->args[1])
		args_exit(terminal()->cmd);
	else
		return (0);
	builtin_redir(cmd, f);
	printf("HERE\n");
	return (1);
}
