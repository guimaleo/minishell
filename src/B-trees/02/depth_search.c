#include <stdlib.h>
#include <stdio.h>

typedef struct	s_btree
{
	int		val;
	struct s_btree	*right;
	struct s_btree	*left;
}		t_btree;

void	print_depth_first(t_btree *root)
{
	t_btree	*process_stack[100];
	size_t	stack_index = 0;
	process_stack[0] = root;
	stack_index++;

	while (stack_index > 0) {
		t_btree	*curr = process_stack[stack_index - 1];
		stack_index--;

		/*In this if you input whatever logic you want to implement in the Btree*/
		if (curr->val == 4){
			printf("Target %i was found\n", curr->val);
			break ;
		}
		else
			printf("%i ", curr->val);
		/*Second output
		if (curr->val == 4)
			printf("%i (node 4 was found!) ", curr->val);
		else
			printf("%i ", curr->val);*/
		/*first output-> printf("%i ", curr->val);*/

		if (curr->right != NULL){
			process_stack[stack_index] = curr->right;
			stack_index++;
		}
		if (curr->left != NULL){
			process_stack[stack_index] = curr->left;
			stack_index++;
		}
	}
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
	3  4 5  6*/

int		main(int ac, char **av)
{
	t_btree	*root = new_node(0);
	root->left = new_node(1);
	root->right = new_node(2);
	root->left->left = new_node(3);
	root->left->right = new_node(4);
	root->right->left = new_node(5);
	root->right->right = new_node(6);

	print_depth_first(root);
}
