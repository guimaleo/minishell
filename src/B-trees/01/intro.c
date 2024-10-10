#include <stdlib.h>
#include <stdio.h>

typedef struct Tree {
	int		value;
	struct Tree	*left;
	struct Tree	*right;
} Tree;

Tree	*new_node(int value)
{
	Tree	*new;

	new = malloc(sizeof(Tree));
	new->value = value;
	new->left = NULL;
	new->right = NULL;

	return (new);
}
//	0
// / \
//1   2

int	main(int ac, char ** av)
{
	Tree	*root = new_node(0);
	root->left = new_node(1);
	root->right = new_node(2);
	printf("Root value: %i\n", root->value);
	printf("Left descendant of root is: %i\n", root->left->value);
	printf("Right descendant of root is: %i\n", root->right->value);

/*Explained before the simplification of the tree init*/
	// Tree	*left = new_node(1);
	// Tree	*right = new_node(2);

/*Explained before to give the understanding for the new_node function*/
	// root->left = malloc(sizeof(Tree));
	// root->left->value = 1;
	// root->left->left = NULL;
	// root->left->right = NULL;
	// root->right = malloc(sizeof(Tree));
	// root->right->value = 2;
	// root->right->left = NULL;
	// root->right->right = NULL;

}
