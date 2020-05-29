#include <stdio.h>
#include <malloc.h>

struct node
{
	int data;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *root;

void insertNode(int);
void deleteNode(struct node*, int);
void display(struct node*, int);

int main()
{
	int option, data;

	do
	{
		printf("\n ******MAIN MENU******* \n");
		printf("\n 1. Insert");
		printf("\n 2. Delete");
		printf("\n 3. Display");
		printf("\n 4. Exit");

		printf("\n\n Enter your option : ");
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("\n Enter the value of the new node : ");
				scanf("%d", &data);
				insertNode(data);
				break;
			case 2:
				printf("\n Enter the value of the node to delete: ");
				scanf("%d", &data);
				deleteNode(root, data);
				break;
			case 3:
				if(root != NULL)
					display(root, 1);
				else
					printf("Tree is empty!\n");
				break;
		}
	} while(option!=4);

	return 0;
}

struct node *findLargestElement(struct node *tree)
{
	if((tree == NULL) || (tree->right == NULL))
		return tree;
	else
		return findLargestElement(tree->right);
}

struct node *grand_parent(struct node *n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

void zig(struct node *n)
{
	struct node *p = n->parent, *g = grand_parent(n);

	printf("ZIG at N: %d P; %d\n", n->data, p->data);
	if(n == p->left)
	{
		p->left = n->right;
		if(n->right != NULL)
			n->right->parent = p;
		n->right = p;
	}
	else
	{
		p->right = n->left;
		if(n->left != NULL)
			n->left->parent = p;
		n->left = p;
	}

	p->parent = n;
	if(g != NULL)
	{
		n->parent = g;
		if(p == g->left)
			g->left = n;
		else
			g->right = n;
	}
	else
	{
		n->parent = NULL;
		root = n;
	}
}

void zag(struct node *n)
{
	struct node *p = n->parent, *g = grand_parent(n);

	printf("ZAG at N: %d P; %d\n", n->data, p->data);
	if(n == p->left)
	{
		p->left = n->right;
		if(n->right != NULL)
			n->right->parent = p;
		n->right = p;
	}
	else
	{
		p->right = n->left;
		if(n->left != NULL)
			n->left->parent = p;
		n->left = p;
	}
	p->parent = n;

	n->parent = g;
	if(p == g->left)
		g->left = n;
	else
		g->right = n;
}

void splay(struct node *n)
{
	while(n != root)
	{
		if(n->parent == root)
			zig(n);
		else
		{
			struct node *p = n->parent, *g = grand_parent(n);
			if((n == p->left && p == g->left) || (n == p->right && p == g->right))
			{
				zig(p);
				zig(n);
			}
			else
			{
				zag(n);
				zig(n);
			}
		}
	}
}

void insertNode(int val)
{
	struct node *ptr, *nodeptr, *parentptr;
	ptr = (struct node*)malloc(sizeof(struct node));
	ptr->data = val;
	ptr->parent = NULL;
	ptr->left = NULL;
	ptr->right = NULL;

	if(root == NULL)
		root = ptr;
	else
	{
		parentptr = NULL;
		nodeptr = root;

		while(nodeptr != NULL)
		{
			parentptr = nodeptr;
			if(val < nodeptr->data)
				nodeptr = nodeptr->left;
			else if(val > nodeptr->data)
				nodeptr = nodeptr->right;
			else
			{
				printf("Duplicate values.\n");
				splay(nodeptr);
				return;
			}
		}
		if(val < parentptr->data)
			parentptr->left = ptr;
		else
			parentptr->right = ptr;

		ptr->parent = parentptr;
		splay(ptr);
	}
}

void deleteNode(struct node *ptr, int data)
{
	if(data < ptr->data && ptr->left)
		deleteNode(ptr->left, data);
	else if(data > ptr->data && ptr->right)
		deleteNode(ptr->right, data);
	else if(data == ptr->data)
	{
		struct node *temp = NULL;
		splay(ptr); // cs.usfca.edu - firstly move to the root then delete
		display(root, 1);

		if(ptr->left && ptr->right)
		{
			temp = findLargestElement(ptr->left);
			ptr->data = temp->data;
			if(temp == temp->parent->left)
				temp->parent->left = NULL;
			else
				temp->parent->right = NULL;
			free(temp);
		}
		else if(ptr->left != NULL)
		{
			ptr = ptr->left;
			ptr->parent = NULL;
		}
		else if(ptr->right != NULL)
		{
			ptr = ptr->right;
			ptr->parent = NULL;
		}
		else
			ptr = NULL;

		root = ptr;
	}
	else
	{
		printf("%d value not found!\n", data);
		splay(ptr);
	}
}

void display(struct node *ptr, int level)
{
	int i;
	if(ptr != NULL)
	{
		display(ptr->right, level+1);
		printf("\n");

		for (i = 0; i < level; i++)
			printf(" ");

		printf("%d", ptr->data);
		display(ptr->left, level+1);
	}
}
