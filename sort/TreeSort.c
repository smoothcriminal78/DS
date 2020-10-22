#include <stdio.h>
#include <stdlib.h>

struct tree
{
	struct tree *left;
	int num;
	struct tree *right;
} ;

void insert (struct tree **tree_node, int num)
{
	if(*tree_node == NULL)
	{
		*tree_node = (struct tree*) malloc(sizeof(struct tree));
		(*tree_node)->left = NULL;
		(*tree_node)->num = num;
		(*tree_node)->right = NULL;
	}
	else
	{
		if(num < (*tree_node)->num)
			insert(&((*tree_node)->left), num);
		else
			insert(&((*tree_node)->right), num);
	}
}

void inorder (struct tree *tree_node)
{
	if(tree_node != NULL)
	{
		inorder(tree_node->left);
		printf("%d\t", tree_node->num);
		inorder(tree_node->right);
	}
}

int main()
{
	struct tree *t;
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	t = NULL ;
	for(int i = 0; i < n; i++)
		insert(&t, arr[i]);

	printf("\nThe sorted array is: \n") ;
	inorder(t) ;

	return 0;
}

