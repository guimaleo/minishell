/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:27 by lede-gui          #+#    #+#             */
/*   Updated: 2024/11/02 17:28:35 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_terminal	*terminal(void)
{
	static t_terminal	init;

	return (&init);
}

// static char	**ft_mingetenv(char **env)
// {
// 	int		i;
// 	int		count;
// 	char	**min_env;

// 	count = 0;
// 	while (env[count])
// 		count++;
// 	i = 0;
// 	min_env = ft_calloc(count + 1, sizeof(char *));
// 	if (!min_env)
// 		return (NULL);
// 	while (env[i])
// 	{
// 		min_env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	return (min_env);
// }

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
		if (!ft_strncmp(terminal()->env[i], str, len))
			break ;
		i++;
	}
	split = ft_split(terminal()->env[i], '=');
	if (split)
		ret = split[1];
	free_doubles((void**)split);
	if (ret)
		return (ret);
	else
		return (NULL);
}

static void	input_looking()
{
	sig_handle();
	while (1)
	{
		terminal()->input = readline("minishell $> ");
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

	terminal()->env = env;
	terminal()->cwd = getcwd(NULL, 0);
	terminal()->old_cwd = ft_getenv("OLDPWD");
	terminal()->home = ft_getenv("HOME");
	input_looking();
}