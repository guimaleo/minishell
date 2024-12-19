/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:27 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 14:44:59 by lede-gui         ###   ########.fr       */
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
}

char	*ft_getenv(char *str)
{
	int		i;
	size_t	len;
	char	*ret;
	char	**split;

	ret = NULL;
	split = NULL;
	i = 0;
	len = ft_strlen(str);
	while (terminal()->env && terminal()->env[i])
	{
		if (!ft_strncmp(terminal()->env[i], str, len) 
			&& terminal()->env[i][len] == '=')
			break ;
		i++;
	}
	if (terminal()->env && terminal()->env[i])
	{
		split = ft_split(terminal()->env[i], '=');
		if (split && split[1])
			ret = ft_strdup(split[1]);
		free_doubles((void **)split);
	}
	return (ret);
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
	if(!lvl)
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
	terminal()->prompt = "minishell $> ";
	while (1)
	{
		terminal()->input = readline(terminal()->prompt);
		if (!terminal()->input)
		{
			clean_exit(terminal()->cmd, 2);
		}
		if (*(terminal())->input == '\0')
			continue ;
		add_history(terminal()->input);
		lexer(terminal()->input);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!*env)
		set_bash_min_env();
	else
	{
		terminal()->env = env;
	}
	terminal()->cwd = getcwd(NULL, 0);
	terminal()->old_cwd = ft_getenv("OLDPWD");
	terminal()->home = ft_getenv("HOME");
	input_looking();
}
