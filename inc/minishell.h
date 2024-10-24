
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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

typedef struct s_tty
{
	char	*prompt;
	char	*input;
	char	**split_input;
	char	*commands;
	char	*args;
}		t_tty;

typedef struct s_env{
//
	char **env;
	char **paths;
}t_env;

typedef struct s_tree {
	int		value;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

/*Terminal emulator*/
int		open_tty(t_tty *term);

/*Strings Utils*/
char	**ft_split(char *str, char c);
void	ft_putstrfd(char *str, int fd);
void	ft_putcharfd(char c, int fd);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, int  n);
size_t  ft_strlen(char *str);


/*Memory Functions*/
void	*ft_calloc(size_t len, size_t size);
void	free_doubles(void **ptr);

/*Trees functions*/
t_tree	*new_node(int value);
void	print_depth_first(t_tree *root);
void	recursive_print_depth_first(t_tree *node);
void	free_btree_stack(t_tree *root);

#endif
