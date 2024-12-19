/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:53:44 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 19:53:51 by lede-gui         ###   ########.fr       */
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
# define MIN_
# define BUILTIN {"cd", "echo", "exit", "export", "unset", "pwd", "env" };
# define CD_ERR "cd: no such file or directory: "
# define EXIT_ERR "minishell: exit: abc: numeric argument required\n"
# define DIGITS "1234567890"
# define CMD "Command not found: "

typedef struct s_redirect
{
	char	*file;
	int		flag;
	bool	heredoc;
	struct s_redirect *next;
}		t_redirect;

typedef struct s_cmd
{
	char			**args;
	char			**abs_build;
	char			*path;
	char			**env;
	int				in;
	int				out;
	int				*all_stat;
	int				ret;
	t_redirect		*redir;
	struct s_cmd	*next;
}		t_cmd;


typedef struct s_tty
{
	char	*name;
	char	*home;
	char	*cwd;
	char	*old_cwd;
	char	*prompt;
	char	*input;
	char	**split_input;
	char	*expand;
	char	**env;
	int		stat;
	int		sig;
	bool	no_env;
	t_cmd	*cmd;

}		t_terminal;


/*Signaling*/
void    sig_handle(void);

/*Execution*/
void	exeggutor(t_cmd *cmd);
int    pipex(t_cmd *cmd);
void    check_acess(t_cmd *cmd);
void	check_redir(t_cmd *cmd);
int		open_redir(t_cmd *cmd, int *fd_in);
int	open_redout(t_cmd *cmd);
void	clear_argso(char **args);
void	check_redout(t_cmd *cmd);
t_redirect	*init_redir(void);
void	clean_redir(t_redirect *redir);
void wait_children(int *all_stat);
void check_here(t_cmd *cmd);

/*Built-ins*/

typedef void	(*builtin_func)(t_cmd *cmd);

int    check_builtin(t_cmd *cmd);
int 	exec_builtin(t_cmd *cmd);
void    cd_f(t_cmd *cmd);
void    echo_f(t_cmd *cmd);
void    env_f(t_cmd *cmd);
void	pwd_f(t_cmd *cmd);
void	unset_f(t_cmd *cmd);
void	clean_exit(t_cmd *cmd, int	i);
void	built_exit(t_cmd *cmd);
void    export_f(t_cmd *cmd);
void	args_exit(t_cmd *cmd);


/*Lexical functions*/
void    lexer(char *input);
void	expansions(t_cmd *cmd);
char	*check_variable(t_cmd *cmd, int *i, int *pos);
char	*inject_expansion(char *input, char *key, char *value);
void	quote_analysis(t_cmd *cmd);
typedef void	(*redir_func)(t_cmd *cmd, char *s, int flag);
t_cmd   *new_cmd(char **args);

/*Terminal emulator*/
int		open_tty(t_terminal *term);
t_terminal		*terminal(void);
char	*ft_getenv(char *str);
void    env_injection(t_cmd *cmd, char *tmp);
void	free_prealloc(void);
void	ft_close(int fd);
void	ft_close_pipe(int *fd);


/*Strings Utils*/
void	ft_putstrfd(char *str, int fd);
int		ft_isdigit(char c);
int		ft_isspace(char c);
void	ft_putcharfd(char c, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		check_char(char *s, char c);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char *s2);
char	*ft_strndup(char *str, int  n);
char	**ft_split(char *str, char c);
size_t	ft_strlen(char *str);
int		ft_atoi(char *s);
char	*ft_substr(char * s, int start, int size);
int     ft_isupper(char c);
char	*ft_itoa(int nb);

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
