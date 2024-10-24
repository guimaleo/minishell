/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:27 by lede-gui          #+#    #+#             */
/*   Updated: 2024/10/25 00:32:51 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tty	*init_tty(void)
{
	static t_tty	init;

	return (&init);
}

void	lexer(t_tty *term)
{
	int		i;
	int		j;
	char	*path;
	char	**path_arr;
	char	*abs_path;

	if (term->env)
		path = getenv("PATH");
	path_arr = ft_split(path, ':');
	i = 0;
	while (term->split_input[i])
	{
		j = 0;
		while (path_arr[j])
		{
			abs_path = ft_strjoin(path_arr[j], term->split_input[i]);
			if (access(abs_path, F_OK | X_OK) == 0)
			{
				printf("É um comando!\n");
				printf("arg: %s\n", term->split_input[i]);
				term->commands++;
				break ;
			}
			free(abs_path);
			j++;
		}
		i++;
	}
}

void	input_looking(t_tty *term)
{
	term->input = readline(GREEN"minishell"CIAN" $> " ESCCLR);
	// printf("%s\n", term->input);
	term->split_input = ft_split(term->input, ' ');
	// for(int i = 0; term->split_input[i]; i++)
	// 	printf("%s\n", term->split_input[i]);
	lexer(term);
}

int	main(int ac, char **av, char **env)
{
	t_tty	*term;

	(void)ac;
	(void)av;
	term = init_tty();
	if (*env)
		term->env = true;
	input_looking(term);
}

// int main(int ac, char *av[], char **env)
// {
// 	int i;
// 	t_env *vars;

// 	if (!env || !*env) //teste env-i só funcionou a partir dessa adição
// 	// TODO	no_env(); // Não podemos dar exit, o programa deve rodar mesmo sem env
// 	vars = (t_env *)calloc(1, sizeof(t_env));
// 	if (!vars)
// 		return (1);
// 	i = 0;
// 	while (env[i])
// 		i++;
// 	vars->env = (char **)calloc(1, (i + 1) * sizeof(char *));
// 	if (!vars->env)
// 		exit(1);
// 	i = 0;
// 	while (env[i])
// 	{
// 		vars->env[i] = ft_strdup(env[i]);
// 		// if (!vars->env[i])
// 		// {
// 		//	 while (i)
// 		//		 free(vars->env[i--]);
// 		// }
// 		if (!ft_strncmp(vars->env[i], "PATH=", 5))
// 			vars->paths = ft_split(vars->env[i], ':');
// 		i++;
// 	}
// 	vars->env[i] = NULL;
// 	i = 0;
// 	while (vars->env[i])
// 	{
// 		//printf("%s\n", vars->env[i]);
// 		//ft_putstrfd(vars->env[i], 1);
// 		free(vars->env[i++]);
// 	}
// 	i = 0;
// 	while (vars->paths[i])
// 	{
// 		//printf("%s\n", vars->env[i]);
// 		ft_putstrfd(vars->paths[i], 1);
// 		free(vars->paths[i++]);
// 	}
// 	free(vars->paths);
// 	free(vars->env);
// 	free(vars);
// }
