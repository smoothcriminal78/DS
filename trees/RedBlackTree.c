#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum { FALSE, TRUE } bool;
typedef enum { RED, BLACK } colour;

struct node *root = NULL;

struct node
{
	int data;
	colour colour;
	bool is_leaf;
	struct node *parent;
	struct node *left;
	struct node *right;
};

void insert_case1(struct node *n);
void insert_case2(struct node *n);
void insert_case3(struct node *n);
void insert_case4(struct node *n);
void insert_case5(struct node *n);

void del_case1(struct node *n);
void del_case2(struct node *n);
void del_case3(struct node *n);
void del_case4(struct node *n);
void del_case5(struct node *n);
void del_case6(struct node *n);

struct node* search(struct node *ptr, int data)
{
	if(ptr!=NULL)
	{
		if(data < ptr->data)
			ptr = search(ptr->left, data);
		else if(data > ptr->data)
			ptr = search(ptr->right, data);
	}

	return ptr;
}


void display(struct node *ptr, int level)
{
	int i;
	/* if(ptr!=NULL) */
	if(!ptr->is_leaf)
	{
		display(ptr->right, level+1);
		printf("\n");

		for (i = 0; i < level; i++)
			printf(" ");

		if(!ptr->is_leaf)
		{
			if(ptr->colour == RED)
				printf("%dR", ptr->data);
			else
				printf("%dB", ptr->data);
		}
		else
			printf("null");

		display(ptr->left, level+1);
	}
}


void inorder(struct node *ptr)
{
	if(ptr!=NULL)
	{
		inorder(ptr->left);
		printf("%d(%d) ", ptr->data, ptr->colour);
		inorder(ptr->right);
	}
}


struct node *findSmallestElement(struct node *tree)
{
	if((tree == NULL) || (tree->left->is_leaf))
		return tree;
	else
		return findSmallestElement(tree->left);
}


struct node *findLargestElement(struct node *tree)
{
	if((tree == NULL) || (tree->right->is_leaf))
		return tree;
	else
		return findLargestElement(tree->right);
}


struct node *sibling(struct node *n)
{
	if (n == n->parent->left)
		return n->parent->right;

	else
		return n->parent->left;
}


struct node *grand_parent(struct node *n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}


struct node *uncle(struct node *n)
{
	struct node *g;
	g = grand_parent(n);
	
	if (g == NULL)
		return NULL;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void create_leaves(struct node *n)
{
	if(n->left == NULL)
	{
		struct node *temp = (struct node*)malloc(sizeof(struct node));
		temp->left = NULL;
		temp->right = NULL;
		temp->data = -1;
		temp->parent = n;
		temp->colour = BLACK;
		temp->is_leaf = TRUE;
		n->left = temp;
	}

	if(n->right == NULL)
	{
		struct node *temp = (struct node*)malloc(sizeof(struct node));
		temp->left = NULL;
		temp->right = NULL;
		temp->data = -1;
		temp->parent = n;
		temp->colour = BLACK;
		temp->is_leaf = TRUE;
		n->right = temp;
	}
}

void rotate_left(struct node *n)
{
	printf("LEFT ROTATION\n");
	struct node *p, *ch;
	p = n->parent;
	ch = n->right;

	n->right = ch->left;
	ch->left->parent = n;
	ch->left = n;
	ch->parent = p;

	if(p == NULL)
		root = ch;
	else
	{
		if(n->parent->left == n)
			p->left = ch;
		else
			p->right = ch;
	}

	n->parent = ch;
}

void rotate_right(struct node *n)
{
	printf("RIGHT ROTATION\n");
	struct node *p, *ch;
	p = n->parent;
	ch = n->left;

	n->left = ch->right;
	ch->right->parent = n;
	ch->right = n;
	ch->parent = p;

	if(p == NULL)
		root = ch;
	else
	{
		if(n->parent->left == n)
			p->left = ch;
		else
			p->right = ch;
	}

	n->parent = ch;
}

// The New Node N is Added as the Root of the Tree
void insert_case1(struct node *n)
{
	if (n->parent == NULL) // Root node
	{
		printf("INSERT CASE1 %d\n", n->data);
		n->colour = BLACK;
	}
	else
		insert_case2(n);
}


// The New Node’s Parent P is Black
void insert_case2(struct node *n)
{
	if (n->parent->colour != BLACK)
		insert_case3(n);
	else
		printf("INSERT CASE2 %d\n", n->data);
}


// If Both the Parent (P) and the Uncle (U) are Red
void insert_case3(struct node *n)
{
	struct node *u, *g;
	u = uncle(n);
	g = grand_parent(n);

	if((u != NULL) && (u->colour == RED))
	{
		printf("INSERT CASE3 %d\n", n->data);
		n->parent->colour = BLACK;
		u->colour = BLACK;
		g->colour = RED;
		insert_case1(g);
	}
	else
		insert_case4(n);
}


// The Parent P is Red but the Uncle U is Black and N is the Right Child of P and P is the Left Child of G
void insert_case4(struct node *n)
{
	struct node *g = grand_parent(n);
	if ((n == n->parent->right) && (n->parent == g->left))
	{
		printf("INSERT CASE4 %d\n", n->data);
		rotate_left(n->parent);
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right))
	{
		printf("INSERT CASE4 %d\n", n->data);
		rotate_right(n->parent);
		n = n->right;
	}

	insert_case5(n);
}	

// The Parent P is Red but the Uncle U is Black and the New Node N is the Left Child of P, and P is the Left Child of its Parent G 
void insert_case5(struct node *n)
{
	struct node *g;
	g = grand_parent(n);

	printf("INSERT CASE5 %d\n", n->data);
	if ((n == n->parent->left) && (n->parent == g->left))
		rotate_right(g);
	else if ((n == n->parent->right) && (n->parent == g->right))
		rotate_left(g);
	n->parent->colour = BLACK;
	g->colour = RED;
}


struct node *insert(int data)
{
	struct node *ptr, *nodeptr, *parentptr;
	ptr = (struct node*)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->left = NULL;
	ptr->right = NULL;
	ptr->colour = RED;
	ptr->is_leaf = FALSE;

	if(root == NULL)
	{
		root=ptr;
		root->left=NULL;
		root->right=NULL;
		root->parent=NULL;
		create_leaves(root);
	}
	else
	{
		parentptr = NULL;
		nodeptr = root;

		while(!nodeptr->is_leaf)
		{
			parentptr = nodeptr;
			if(data < nodeptr->data)
				nodeptr = nodeptr->left;
			else
				nodeptr = nodeptr->right;
		}
		if(data < parentptr->data)
			parentptr->left = ptr;
		else
			parentptr->right = ptr;
		ptr->parent = parentptr;
		free(nodeptr);
		create_leaves(ptr);
	}

	insert_case1(ptr);
}

// N is the New Root
void del_case1(struct node *n)
{
	if(n->parent != NULL)
		del_case2(n);
	else
		printf("DELETE CASE1 %d\n", n->data);
}

// Sibling S is Red
void del_case2(struct node *n)
{
	struct node *s;

	s = sibling(n);
	if(s->colour == RED)
	{
		printf("DELETE CASE2 %d\n", n->data);
		if(n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
		n->parent->colour = RED;
		s->colour = BLACK;
	}

	del_case3(n);
}

// P, S, and S’s Children are Black
void del_case3(struct node *n)
{
	struct node *s;

	s = sibling(n);
	if((n->parent->colour == BLACK) && (s->colour == BLACK) && (s->left->colour == BLACK) && (s->right->colour == BLACK))
	{
		printf("DELETE CASE3 %d\n", n->data);
		s->colour = RED;
		del_case1(n->parent);
	}
	else
		del_case4(n);
}

// S and S’s Children are Black, but P is Red
void del_case4(struct node *n)
{
	struct node *s;

	s = sibling(n);
	if((n->parent->colour == RED) && (s->colour == BLACK) && (s->left->colour == BLACK) && (s->right->colour == BLACK))
	{
		printf("DELETE CASE4 %d\n", n->data);
		s->colour = RED;
		n->parent->colour = BLACK;
	}
	else
		del_case5(n);
}

// N is the Left Child of P and S is Black, S’s Left Child is Red, S’s Right Child is Black
void del_case5(struct node *n)
{
	struct node *s;

	s = sibling(n);
	if(s->colour == BLACK)
	{
		printf("DELETE CASE5 %d\n", n->data);
		/* the following code forces the red to be on the left of the left of the parent,
		  or right of the right, to be correctly operated in case 6. */
		if((n == n->parent->left) && (s->right->colour == BLACK) && (s->left->colour == RED))
			rotate_right(s);
		else if((n == n->parent->right) && (s->left->colour == BLACK) && (s->right->colour == RED))
			rotate_left(s);
		s->colour = RED;
		s->right->colour = BLACK;
	}

	del_case6(n);
}

// S is Black, S’s Right Child is Red, and N is the Left Child of its Parent P
void del_case6(struct node *n)
{
	struct node *s;
	s = sibling(n);

	printf("DELETE CASE6 %d\n", n->data);

	s->colour = n->parent->colour;
	n->parent->colour = BLACK;
	if(n == n->parent->left)
	{
		s->right->colour = BLACK;
		rotate_left(n->parent);
	}
	else
	{
		s->left->colour = BLACK;
		rotate_right(n->parent);
	}
}


void replace_node(struct node *n, struct node *child)
{
	if(n == root)
		root = child;
	else
	{
		if(n == n->parent->right)
			n->parent->right = child;
		else
			n->parent->left = child;
	}

	child->parent = n->parent;
}


void delete_child(struct node *n)
{
	struct node *child;

	if(n->right->is_leaf)
		child = n->left;
	else
		child = n->right;

	replace_node(n, child);
	if(n->colour == BLACK)
	{
		if(child->colour == RED)
			child->colour = BLACK;
		else
			del_case1(child);
	}

	free(n);
}


void deleteElement(struct node *tree, int val)
{
	struct node *temp;

	if(tree==NULL)
	{
		printf("\n The tree is empty ");
	}
	else if(val < tree->data)
	{
		deleteElement(tree->left, val);
	}
	else if(val > tree->data)
	{
		deleteElement(tree->right, val);
	}
	else if(!tree->left->is_leaf && !tree->right->is_leaf)
	{
		temp = findLargestElement(tree->left);
		tree->data = temp->data;
		deleteElement(tree->left, temp->data);
	}
	else
	{
		if(tree->parent == NULL)
			root = NULL;
		else
			delete_child(tree);
	}
}


int main()
{
	int data;
	int option;

	while(1)
	{
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Display\n");
		printf("4.Quit\n");
		printf("Enter your option : ");
		scanf("%d",&option);

		switch(option)
		{
			case 1:
				printf("Enter the value to be inserted : ");
				scanf("%d", &data);
				if(search(root, data) == NULL)
					insert(data);
				else
					printf("Duplicate value ignored\n");
				break;
			case 2:
				printf("Enter the value to be deleted : ");
				scanf("%d", &data);
				if(search(root, data) == NULL)
					printf("Value not found!\n");
				else
					deleteElement(root, data);
				break;
			case 3:
				if(root==NULL)
				{
					printf("Tree is empty\n");
					continue;
				}

				printf("Tree is :\n");
				display(root, 1);
				printf("\n\n");
				printf("Inorder Traversal is: ");
				inorder(root);
				printf("\n");
				break;
			case 4:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
