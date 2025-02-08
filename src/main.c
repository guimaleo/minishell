/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:27 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 21:53:44 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_terminal	*terminal(void)
{
	static t_terminal	init;

	return (&init);
}

void	free_prealloc(void)
{
	if (terminal()->cwd)
	{
		free(terminal()->cwd);
		terminal()->cwd = NULL;
	}
	if (terminal()->old_cwd)
	{
		free(terminal()->old_cwd);
		terminal()->old_cwd = NULL;
	}
	if (terminal()->home)
	{
		free(terminal()->home);
		terminal()->home = NULL;
	}
	if (terminal()->env)
	{
		free_doubles((void **)terminal()->env);
		terminal()->env = NULL;
	}
}

void	set_bash_min_env(void)
{
	char	*path;
	char	*lvl;
	char	**min;

	printf("No env case\n");
	terminal()->no_env = true;
	terminal()->cwd = getcwd(NULL, 0);
	path = MIN_PATH;
	lvl = getenv("SHLVL");
	if (!lvl)
		lvl = "1";
	min = ft_calloc(4, sizeof(char *));
	if (!min)
	{
		perror("env init");
		exit(EXIT_FAILURE);
	}
	min[0] = ft_strjoin("PATH=", path);
	min[1] = ft_strjoin("PWD=", terminal()->cwd);
	min[2] = ft_strjoin("SHLVL=", lvl);
	min[3] = NULL;
	terminal()->env = min;
}

static void	input_looking(void)
{
	sig_handle();
	while (1)
	{
		terminal()->prompt = "minishell $> ";
		terminal()->input = readline(terminal()->prompt);
		if (!terminal()->input)
		{
			clean_exit(terminal()->cmd, 2);
		}
		if (*(terminal())->input == '\0')
			continue ;
		add_history(terminal()->input);
		ft_check();
		if (terminal()->input)
			lexer(terminal()->input);
		else
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!*env)
		set_bash_min_env();
	else
		ft_copyenv(env);
	terminal()->cwd = getcwd(NULL, 0);
	terminal()->old_cwd = ft_getenv("OLDPWD");
	terminal()->home = ft_getenv("HOME");
	input_looking();
}
