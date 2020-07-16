#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h> 

#define MAX_KEYS (5)

typedef enum { FALSE, TRUE } bool;

struct node *root = NULL;

struct node
{
	bool is_leaf;
	int numKeys;
	int keys[MAX_KEYS];
	struct node *children[MAX_KEYS+1];
	struct node *parent;
};

struct node* search(struct node *ptr, int data)
{
	if(ptr != NULL && ptr->numKeys > 0)
	{
		for (int i = 0; i < ptr->numKeys; i++)
		{
			if(data == ptr->keys[i])
				return ptr;
			else if(data < ptr->keys[i])
				return search(ptr->children[i], data);
		}
		return search(ptr->children[ptr->numKeys], data);
	}
}

void display(struct node *ptr, int level)
{
	if(ptr != NULL)
	{
		for(int i = ptr->numKeys; i > 0; i--)
		{
			display(ptr->children[i], level+1);
			for (int j = 0; j < level; j++)
				printf(" ");
			printf("%d\n", ptr->keys[i-1]);
		}
		display(ptr->children[0], level+1);
	}
}

struct node *split(struct node *ptr)
{
	struct node *right, *median;

	right = (struct node*)malloc(sizeof(struct node));
	right->is_leaf = ptr->is_leaf;
	right->numKeys = 0;

	ptr->numKeys = floor(MAX_KEYS / 2);
	for(int i = ptr->numKeys+1; i < MAX_KEYS; i++)
	{
			right->keys[right->numKeys] = ptr->keys[i];
		ptr->keys[i] = -1;
		right->children[right->numKeys] = ptr->children[i];
		if(right->children[right->numKeys] != NULL)
			right->children[right->numKeys]->parent = right;
		ptr->children[i] = NULL;
		right->numKeys++;
	}
	right->children[right->numKeys] = ptr->children[MAX_KEYS];
	if(right->children[right->numKeys] != NULL)
		right->children[right->numKeys]->parent = right;
	ptr->children[MAX_KEYS] = NULL;

	median = (struct node*)malloc(sizeof(struct node));
	median->is_leaf = FALSE;
	median->numKeys = 1;
	median->keys[0] = ptr->keys[ptr->numKeys];
	ptr->keys[ptr->numKeys] = -1;
	median->children[0] = ptr;
	median->children[1] = right;

	ptr->parent = median;
	right->parent = median;

	return median;
}

void printNode(struct node *ptr)
{
	printf("Keys: \n");
	for (int i = 0; i < ptr->numKeys; i++)
	{
		printf("Key: %d ", ptr->keys[i]);
		printf("Children: ");
		if(ptr->children[i] != NULL)
		{
			for (int j = 0; j < ptr->children[i]->numKeys; j++)
				printf(":%d:", ptr->children[i]->keys[j]);		
		}
		else
			printf(":NULL:");		
	}

	printf(" :: ");
	if(ptr->children[ptr->numKeys] != NULL)
	{
		for (int j = 0; j < ptr->children[ptr->numKeys]->numKeys; j++)
			printf(":%d:", ptr->children[ptr->numKeys]->keys[j]);		
	}
	else
		printf(":NULL:");		
	printf("\n");
}

struct node *predecessor(struct node *ptr)
{
	if(!ptr->is_leaf)
		return predecessor(ptr->children[ptr->numKeys]);

	return ptr;	
}

struct node *merge(struct node *parent, int i)
{
	struct node *n1 = parent->children[i], *n2 = parent->children[i+1];

	n1->keys[n1->numKeys++] = parent->keys[i];

	if(i < parent->numKeys)
	{
		for (int j = i+1; j < parent->numKeys; ++j)
		{
			parent->keys[j-1] = parent->keys[j];
			parent->children[j] = parent->children[j+1];
		}
	}

	parent->keys[parent->numKeys-1] = -1;
	parent->children[parent->numKeys] = NULL;
	parent->numKeys--;

	for (int i = 0; i < n2->numKeys; i++)
	{
		n1->children[n1->numKeys] = n2->children[i];	
		if(n1->children[n1->numKeys] != NULL)
			n1->children[n1->numKeys]->parent = n1;

		n1->keys[n1->numKeys++] = n2->keys[i];	
	}

	n1->children[n1->numKeys] = n2->children[n2->numKeys];	

	if(n1->children[n1->numKeys] != NULL)
		n1->children[n1->numKeys]->parent = n1;

	return n1;
}

int insertKey(struct node *ptr, int data)
{
	int pos = -1;
	for (int i = 0; i < ptr->numKeys; i++)
	{
		if(data == ptr->keys[i])
			return i;
		if(data < ptr->keys[i])
		{
			for (int j = ptr->numKeys; j > i; j--)
				ptr->keys[j] = ptr->keys[j-1];					
			pos = i;
			break;
		}
	}

	if(pos == -1)
		pos = ptr->numKeys;

	ptr->keys[pos] = data;
	ptr->numKeys++;

	return pos;
}

void deleteKey(struct node *ptr, int i)
{
	for (int j = i; j < ptr->numKeys-1; ++j)
		ptr->keys[j] = ptr->keys[j+1];

	ptr->keys[ptr->numKeys-1] = -1;
	ptr->numKeys--;
}

struct node *balance(struct node *ptr)
{
	struct node *parent = ptr->parent;

	if(parent == NULL)
		return ptr;

	struct node *left = NULL, *right = NULL;
	int pos = -1;
	for(int j = 0; j <= parent->numKeys; j++)
	{
		if(parent->children[j] == ptr)	
		{
			pos = j;
			if(pos == 0)
				right = parent->children[pos+1];
			else if(pos == parent->numKeys)
				left = parent->children[pos-1];
			else
			{
				left = parent->children[pos-1];
				right = parent->children[pos+1];
			}
			break;
		}
	}

	if(left != NULL && left->numKeys > floor(MAX_KEYS / 2))
	{
		/* printf("Taking from left sibling\n"); */
		for (int j = ptr->numKeys; j >= 0; j--)
		{
			if(j > 0)
				ptr->keys[j] = ptr->keys[j-1];
			ptr->children[j+1] = ptr->children[j];
		}
		ptr->keys[0] = parent->keys[pos-1];
		ptr->children[0] = left->children[left->numKeys];
		ptr->numKeys++;

		parent->keys[pos-1] = left->keys[left->numKeys-1];

		left->keys[left->numKeys-1] = -1;
		left->children[left->numKeys] = NULL;
		left->numKeys--;
	}
	else if(right != NULL && right->numKeys > floor(MAX_KEYS / 2))
	{
		/* printf("Taking from right sibling\n"); */
		ptr->keys[ptr->numKeys] = parent->keys[pos];
		ptr->children[ptr->numKeys+1] = right->children[0];
		ptr->numKeys++;

		parent->keys[pos] = right->keys[0];

		for (int j = 1; j <= right->numKeys; ++j)
		{
			if(j < right->numKeys)
				right->keys[j-1] = right->keys[j]; 		
			right->children[j-1] = right->children[j]; 		
		}
		right->keys[right->numKeys-1] = -1;
		right->children[right->numKeys-1] = NULL;
		right->numKeys--;
	}
	else if(left != NULL)
	{
		/* printf("Merging with left sibling\n"); */
		ptr = merge(parent, pos-1);
	}
	else if(right != NULL)
	{
		/* printf("Merging with right sibling\n"); */
		ptr = merge(parent, pos);
	}

	if(parent != NULL && parent->numKeys < floor(MAX_KEYS / 2))
		ptr->parent = balance(parent);

	return ptr;
}

struct node *insert(struct node *ptr, int data)
{
	if(ptr == NULL)
	{
		ptr = (struct node*)malloc(sizeof(struct node));
		ptr->numKeys = 1;
		ptr->keys[0] = data;
		ptr->is_leaf = TRUE;

		return ptr;
	}
	else if(!ptr->is_leaf)
	{
		ptr->is_leaf = FALSE;
		struct node *temp = NULL;
		int pos = -1;
		for(int i = 0; i < ptr->numKeys; i++)
		{
			if(data == ptr->keys[i])
				return ptr;
			else if(data < ptr->keys[i])
			{
				temp = insert(ptr->children[i], data);
				pos = i;
				break;
			}
		}

		if(pos == -1)
		{
			temp = insert(ptr->children[ptr->numKeys], data);
			pos = ptr->numKeys;
		}

		if(temp != ptr->children[pos])
		{
			int key_pos = insertKey(ptr, temp->keys[0]);

			ptr->children[key_pos] = temp->children[0];
			ptr->children[key_pos]->parent = ptr;

			for(int i = ptr->numKeys+1; i > key_pos+1; i--)
				ptr->children[i] = ptr->children[i-1];					

			ptr->children[key_pos+1] = temp->children[1];
			ptr->children[key_pos+1]->parent = ptr;
		}
	}
	else
		insertKey(ptr, data);

	if(ptr->numKeys == MAX_KEYS)
		ptr = split(ptr);	

	return ptr;
}


struct node *deleteElement(struct node *ptr, int val)
{
	if(ptr == NULL)
	{
		printf("No such node %d\n", val);
		exit(0);
	}

	for(int i = 0; i < ptr->numKeys; i++)
	{
		if(ptr->keys[i] == val)
		{
			if(ptr->is_leaf)
			{
				deleteKey(ptr, i);

				if(ptr->parent != NULL && ptr->numKeys < floor(MAX_KEYS / 2))
					ptr = balance(ptr);

				// Rewind to the root element
				while(ptr->parent != NULL)
				{
					if(ptr->parent->numKeys == 0)
					{
						ptr->parent = NULL;
						break;
					}
					ptr = ptr->parent;
				}

				return ptr;
			}
			else
			{
				struct node *child = ptr->children[i];
				
				struct node *pred = predecessor(child);	
				ptr->keys[i] = pred->keys[pred->numKeys-1];

				return deleteElement(child, pred->keys[pred->numKeys-1]);
			}
		}
		else if(ptr->keys[i] > val)
		{
			return deleteElement(ptr->children[i], val);
		}
	}

	return deleteElement(ptr->children[ptr->numKeys], val);
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
		printf("4.Search\n");
		printf("5.Quit\n");
		printf("Enter your option : ");
		scanf("%d",&option);

		switch(option)
		{
			case 1:
				printf("Enter the value to be inserted : ");
				scanf("%d", &data);
				root = insert(root, data);
				break;
			case 2:
				printf("Enter the value to be deleted : ");
				scanf("%d", &data);
				root = deleteElement(root, data);
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
				/* printf("Inorder Traversal is: "); */
				/* inorder(root); */
				/* printf("\n"); */
				break;
			case 4:
				printf("Enter the value to be searched : ");
				scanf("%d", &data);
				struct node *val = search(root, data);
				printf("Value: %d is found.\n", val->keys[0]);
				break;
			case 5:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
