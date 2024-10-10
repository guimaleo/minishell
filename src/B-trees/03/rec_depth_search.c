#include <stdlib.h>
#include <stdio.h>

typedef struct	s_btree
{
	int		val;
	struct s_btree	*right;
	struct s_btree	*left;
}		t_btree;

// int	found = 0;
void	recursive_print_depth_first(t_btree *node)
{
	// if (found == 1)
	// 	return ;
	if (node->val == 4){
		printf("Target %i found!\n", node->val);
		// found = 1;
		return ;
	}
	else
		printf("%i ", node->val);
	if (node->left != NULL)
		recursive_print_depth_first(node->left);
	if (node->right != NULL)
		recursive_print_depth_first(node->right);
}

t_btree	*new_node(int val)
{
	t_btree	*new;

	new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/*		0
	   / \
	  1   2
	 / \ / \
	3  4 5  6
	  / \
	 7   8/*/

int		main(int ac, char **av)
{
	t_btree	*root = new_node(0);
	root->left = new_node(1);
	root->right = new_node(2);
	root->left->left = new_node(3);
	root->left->right = new_node(4);
	root->right->left = new_node(5);
	root->right->right = new_node(6);
	root->left->right->left = new_node(7);
	root->left->right->right = new_node(8);

	recursive_print_depth_first(root);
}
