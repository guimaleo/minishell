/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:53:44 by lede-gui          #+#    #+#             */
/*   Updated: 2024/11/02 17:54:07 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "colors.h"

# define MIN_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define BUILTIN {"cd", "echo", "exit", "export", "unset", "pwd", "env" };
# define CD_ERR "cd: no such file or directory: "

typedef struct s_env
{
	char **env;
	//char **paths;  Nao precisa
}		t_env;

typedef struct s_redirect
{
	char	*file;
	bool	in;
	t_redirect *next;
}		t_redirect;

typedef struct s_cmd
{
	char			**args;
	char			**abs_build;
	char			*path;
	char			**env;
	int				in;
	int				out;
	t_redirect		*redir;
	struct s_cmd	*next;
}		t_cmd;


typedef struct s_tty
{
	char	*name;
	char	*prompt;
	char	*input;
	char	**split_input;
	char	**env;
	t_cmd	*cmd;

}		t_terminal;


/*Execution*/
void	exeggutor(t_cmd *cmd);
void    pipex(t_cmd *cmd);
void    check_acess(t_cmd *cmd);
void	check_redir(t_cmd *cmd);

/*Built-ins*/

typedef void	(*builtin_func)(t_cmd *cmd);

int    check_builtin(t_cmd *cmd);
int 	exec_builtin(t_cmd *cmd);
void    cd_f(t_cmd *cmd);
void    echo_f(t_cmd *cmd);
void    env_f(t_cmd *cmd);
void   unset_f(t_cmd *cmd);
void	clean_exit(t_cmd *cmd, int	i);
void    export_f(t_cmd *cmd);


/*Lexical functions*/
void    lexer(char *input);
t_cmd   *new_cmd(char **args);

/*Terminal emulator*/
int		open_tty(t_terminal *term);
t_terminal		*terminal(void);


/*Strings Utils*/
void	ft_putstrfd(char *str, int fd);
void	ft_putcharfd(char c, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char *s2);
char	*ft_strndup(char *str, int  n);
char	**ft_split(char *str, char c);
size_t	ft_strlen(char *str);


/*Memory Functions*/
void	*ft_calloc(size_t len, size_t size);
void	free_doubles(void **ptr);
void	free_list(t_cmd **list);

// /*Trees functions*/
// t_tree	*new_node(int value);
// void	print_depth_first(t_tree *root);
// void	recursive_print_depth_first(t_tree *node);
// void	free_btree_stack(t_tree *root);

#endif
