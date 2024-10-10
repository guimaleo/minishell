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

void	free_btree_queue(t_btree *root)
{
	t_btree	*process_queue[100];
	size_t	queue_index = 0;
	process_queue[0] = root;
	queue_index++;

	int	i = 0;
	while (i < queue_index){
		t_btree *curr = process_queue[i];
		i++;

		if (curr->left != NULL){
			process_queue[queue_index] = curr->left;
			queue_index++;
		}
		if (curr->right != NULL){
			process_queue[queue_index] = curr->right;
			queue_index++;
		}
		free(curr);
	}
	// i = (queue_index - 1);
	// while (i >= 0){
	// 	free(process_queue[i--]);
	// }
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

void	free_btree_stack(t_btree *root) {
	t_btree	*process_stack[100];
	size_t	process_index = 0;
	process_stack[0] = root;
	process_index++;

	while (process_index > 0) {
		t_btree *curr = process_stack[process_index - 1];
		process_index--;

		if (curr->right != NULL){
			process_stack[process_index] = curr->right;
			process_index++;
		}
		if (curr->left != NULL){
			process_stack[process_index] = curr->left;
			process_index++;
		}
		printf("\nFreeing %i\nProcess index:%lu\n", curr->val, process_index);
		free(curr);
	}
}

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
	root->left->right->left->left = new_node(9);
	root->left->right->left->right = new_node(10);

	recursive_print_depth_first(root);
	//free_btree_queue(root);
	free_btree_stack(root);
}
