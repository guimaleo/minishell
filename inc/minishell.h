
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

typedef struct s_env{
//
    char **env;
}t_env;

typedef struct s_tree {
	int		value;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

/*Trees functions*/
t_tree	*new_node(int value);
void	print_depth_first(t_tree *root);
void	recursive_print_depth_first(t_tree *node);
void	free_btree_stack(t_tree *root);

#endif