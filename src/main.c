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



static void	input_looking()
{
	while (1)
	{
		terminal()->input = readline("minishell $> ");
		if (!terminal()->input || *(terminal())->input == '\0')
			continue ;
		add_history(terminal()->input);
		lexer(terminal()->input);

		//free(terminal()->input);
	}
	printf("%s\n", terminal()->input);
	// for(int i = 0; terminal()->split_input[i]; i++)
	// 	printf("%s\n", terminal()->split_input[i]);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;


	terminal()->env = env;
	terminal()->cwd = getcwd(NULL, 0);
	// TROCAR GETENV POR FT_GETENV
	terminal()->old_cwd = getenv("OLDPWD");
	terminal()->home = getenv("HOME");
	input_looking();
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
