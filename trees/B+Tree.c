#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h> 

#define MAX_KEYS (5) // split when number of keys equal to MAX_KEYS

typedef enum { FALSE, TRUE } bool;

struct inode *root = NULL;
struct dnode *data_root = NULL;

struct dnode
{
	struct dnode *next;
	int numKeys;
	int keys[MAX_KEYS];
};

struct inode
{
	bool is_leaf;
	int numKeys;
	int keys[MAX_KEYS];
	struct inode *children[MAX_KEYS+1];
	struct inode *parent;
    struct dnode *data[MAX_KEYS+1];
};

void displayIndex(struct inode *ptr, int level)
{
	if(ptr != NULL)
	{
		for(int i = ptr->numKeys; i > 0; i--)
		{
			if(!ptr->is_leaf)
				displayIndex(ptr->children[i], level+1);
			for (int j = 0; j < level; j++)
				printf(" ");
			printf("%d", ptr->keys[i-1]);
			if(ptr->is_leaf)
			{
				struct dnode *d = ptr->data[i];
				printf(" (");
				for (int j = 0; j < d->numKeys; j++)
					printf("%d,", d->keys[j]);
				printf(")");
			}
			printf("\n");
		}
		if(ptr->is_leaf)
		{
			for (int j = 0; j < level; j++)
				printf(" ");
			struct dnode *d_first = ptr->data[0];
			printf(" (");
			for (int j = 0; j < d_first->numKeys; j++)
				printf("%d,", d_first->keys[j]);
			printf(")\n");
		}
		if(!ptr->is_leaf)
			displayIndex(ptr->children[0], level+1);
	}
}

void displayData(struct dnode *ptr)
{
	while(ptr != NULL)
	{
		printf("[");
		for (int i = 0; i < ptr->numKeys; i++)
		{
			printf("%d,", ptr->keys[i]);
		}
		printf("], ");
		ptr = ptr->next;
	}
}

struct inode *split(struct inode *ptr)
{
	struct inode *right, *median;

	right = (struct inode*)malloc(sizeof(struct inode));
	right->is_leaf = ptr->is_leaf;
	right->numKeys = 0;
	ptr->numKeys = floor(MAX_KEYS / 2);

	if(ptr->is_leaf)
	{
		for(int i = ptr->numKeys+1; i < MAX_KEYS; i++)
		{
			right->keys[right->numKeys] = ptr->keys[i];
			ptr->keys[i] = -1;

			right->data[right->numKeys++] = ptr->data[i];
			ptr->data[i] = NULL;
		}
		right->data[right->numKeys] = ptr->data[MAX_KEYS];
		ptr->data[MAX_KEYS] = NULL;
	}
	else
	{
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
	}

	median = (struct inode*)malloc(sizeof(struct inode));
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


struct inode *splitData(struct dnode *ptr)
{
	struct dnode *right = (struct dnode*)malloc(sizeof(struct dnode));
	right->numKeys = 0;
	right->next = ptr->next;

	ptr->numKeys = floor(MAX_KEYS / 2);
	ptr->next = right;
	for(int i = ptr->numKeys; i < MAX_KEYS; i++)
	{
		right->keys[right->numKeys++] = ptr->keys[i];
		ptr->keys[i] = -1;
	}

	struct inode *median = (struct inode*)malloc(sizeof(struct inode));
	median->is_leaf = TRUE;
	median->numKeys = 1;
	median->keys[0] = right->keys[0];
	median->data[0] = ptr;
	median->data[1] = right;

	return median;
}

void printNode(struct inode *ptr)
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

struct inode *predecessor(struct inode *ptr)
{
	if(!ptr->is_leaf)
		return predecessor(ptr->children[ptr->numKeys]);

	return ptr;	
}

struct inode *merge(struct inode *parent, int i)
{
	struct inode *n1 = parent->children[i], *n2 = parent->children[i+1];

	if(n2->is_leaf && n2->numKeys == 0)
		n1->keys[n1->numKeys++] = n2->data[0]->keys[0];
	else
		n1->keys[n1->numKeys++] = parent->keys[i];

	if(i < parent->numKeys)
	{
		for (int j = i+1; j < parent->numKeys; ++j)
		{
			parent->keys[j-1] = parent->keys[j];
			parent->children[j] = parent->children[j+1];
			parent->data[j] = parent->data[j+1];
		}
	}

	parent->keys[parent->numKeys-1] = -1;
	parent->children[parent->numKeys] = NULL;
	parent->data[parent->numKeys] = NULL;
	parent->numKeys--;

	for (int i = 0; i < n2->numKeys; i++)
	{
		n1->children[n1->numKeys] = n2->children[i];	
		n1->data[n1->numKeys] = n2->data[i];	
		if(n1->children[n1->numKeys] != NULL)
			n1->children[n1->numKeys]->parent = n1;

		n1->keys[n1->numKeys++] = n2->keys[i];	
	}

	n1->children[n1->numKeys] = n2->children[n2->numKeys];	
	n1->data[n1->numKeys] = n2->data[n2->numKeys];	

	if(n1->children[n1->numKeys] != NULL)
		n1->children[n1->numKeys]->parent = n1;

	return n1;
}


int insertIndexKey(struct inode *ptr, int data)
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

int insertKey(struct dnode *ptr, int data)
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

int getDataNodePos(struct inode *ptr, int val)
{
	for (int i = 0; i < ptr->numKeys; ++i)
		if(ptr->keys[i] > val)
			return i;

	return ptr->numKeys;
}

int getPos(struct dnode *ptr, int val)
{
	for (int i = 0; i < ptr->numKeys; ++i)
		if(ptr->keys[i] == val)
			return i;

	return -1;
}

int search(struct inode *ptr, int data)
{
	if(ptr != NULL && ptr->numKeys > 0)
	{
		for (int i = 0; i < ptr->numKeys; i++)
		{
			if(data < ptr->keys[i])
			{
				if(ptr->is_leaf)
					return getPos(ptr->data[i], data);

				return search(ptr->children[i], data);
			}
		}

		if(ptr->is_leaf)
			return getPos(ptr->data[ptr->numKeys], data);

		return search(ptr->children[ptr->numKeys], data);
	}
}

void deleteIndexKey(struct inode *ptr, int i)
{
	for (int j = i; j < ptr->numKeys-1; ++j)
		ptr->keys[j] = ptr->keys[j+1];
	ptr->keys[ptr->numKeys-1] = -1;
	ptr->numKeys--;
}

void deleteKey(struct dnode *ptr, int i)
{
	for (int j = i; j < ptr->numKeys-1; ++j)
		ptr->keys[j] = ptr->keys[j+1];
	ptr->keys[ptr->numKeys-1] = -1;
	ptr->numKeys--;
}

struct inode *balance(struct inode *ptr)
{
	struct inode *parent = ptr->parent;

	if(parent == NULL)
		return ptr;

	struct inode *left = NULL, *right = NULL;
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

	if(left != NULL && left->numKeys > floor((MAX_KEYS-1) / 2))
	{
		/* printf("Taking from left sibling\n"); */
		for (int j = ptr->numKeys; j >= 0; j--)
		{
			if(j > 0)
				ptr->keys[j] = ptr->keys[j-1];
			ptr->children[j+1] = ptr->children[j];
			ptr->data[j+1] = ptr->data[j];
		}

		ptr->keys[0] = parent->keys[pos-1];

		ptr->children[0] = left->children[left->numKeys];
		ptr->data[0] = left->data[left->numKeys];
		ptr->numKeys++;

		parent->keys[pos-1] = left->keys[left->numKeys-1];

		left->keys[left->numKeys] = -1;
		left->children[left->numKeys] = NULL;
		left->data[left->numKeys] = NULL;
		left->numKeys--;
	}
	else if(right != NULL && right->numKeys > floor((MAX_KEYS-1) / 2))
	{
		/* printf("Taking from right sibling\n"); */
		ptr->keys[ptr->numKeys++] = parent->keys[pos];
		ptr->children[ptr->numKeys] = right->children[0];
		ptr->data[ptr->numKeys] = right->data[0];

		parent->keys[pos] = right->keys[0];

		for (int j = 1; j <= right->numKeys; ++j)
		{
			if(j < right->numKeys)
				right->keys[j-1] = right->keys[j]; 		
			right->children[j-1] = right->children[j]; 		
			right->data[j-1] = right->data[j]; 		
		}

		right->numKeys--;
		right->keys[right->numKeys] = -1;
		right->children[right->numKeys] = NULL;
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

	if(parent != NULL && parent->numKeys < floor((MAX_KEYS-1) / 2))
		ptr->parent = balance(parent);

	return ptr;
}

struct inode *balanceData(struct inode *ptr, int i)
{
	if(ptr->numKeys == 0)
		return ptr;

	struct dnode *d = ptr->data[i];
	struct dnode *left = NULL;
	struct dnode *right = NULL;

	if(i == 0)
		right = ptr->data[i+1];
	else if(i == ptr->numKeys)
		left = ptr->data[i-1];
	else
	{
		left = ptr->data[i-1];
		right = ptr->data[i+1];
	}

	if(left != NULL && left->numKeys > floor((MAX_KEYS-1) / 2))
	{
		/* printf("Taking from left data node\n"); */
		insertKey(d, left->keys[left->numKeys-1]);
		deleteKey(left, left->numKeys-1);
		ptr->keys[i-1] = d->keys[0];
	}
	else if(right != NULL && right->numKeys > floor((MAX_KEYS-1) / 2))
	{
		/* printf("Taking from right data node\n"); */
		insertKey(d, right->keys[0]);
		deleteKey(right, 0);
		ptr->keys[i] = right->keys[0];
		if(i > 0)
			ptr->keys[i-1] = d->keys[0];
	}
	else if(left != NULL)
	{
		/* printf("Merging with left data node\n"); */
		for (int j = 0; j < d->numKeys; j++)
			left->keys[left->numKeys++]	= d->keys[j];

		if(right == NULL)
			left->next = d->next;
		else
			left->next = right;

		for (int j = i; j < ptr->numKeys; j++)
		{
			ptr->keys[j-1] = ptr->keys[j];
			ptr->data[j] = ptr->data[j+1];
		}
		ptr->numKeys--;
	}
	else if(right != NULL)
	{
		/* printf("Merging with right data node\n"); */
		for (int j = 0; j < right->numKeys; j++)
			d->keys[d->numKeys++] = right->keys[j];
		d->next = right->next;

		for (int j = i+1; j < ptr->numKeys; j++)
		{
			ptr->keys[j-1] = ptr->keys[j];
			ptr->data[j] = ptr->data[j+1];
		}
		ptr->numKeys--;

		if(ptr->numKeys > 0)
			ptr->keys[0] = right->next->keys[0];
	}

	return ptr;
}

struct inode *insert(struct inode *ptr, int data)
{
	if(ptr == NULL)
	{
		data_root = (struct dnode*)malloc(sizeof(struct dnode));
		data_root->keys[0] = data;
		data_root->numKeys = 1;

		ptr = (struct inode*)malloc(sizeof(struct inode));
		ptr->is_leaf = TRUE;
		ptr->numKeys = 0;
		ptr->data[0] = data_root;

		return ptr;
	}

	if(!ptr->is_leaf)
	{
		struct inode *temp = NULL;
		int pos = -1;
		for(int i = 0; i < ptr->numKeys; i++)
		{
			if(data <= ptr->keys[i])
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
			int key_pos = insertIndexKey(ptr, temp->keys[0]);

			ptr->children[key_pos] = temp->children[0];
			ptr->children[key_pos]->parent = ptr;

			for(int i = ptr->numKeys+1; i > key_pos+1; i--)
				ptr->children[i] = ptr->children[i-1];					

			ptr->children[key_pos+1] = temp->children[1];
			ptr->children[key_pos+1]->parent = ptr;
		}
	}
	else
	{
		int p = -1;
		for (int i = 0; i < ptr->numKeys; i++)
		{
			if(data < ptr->keys[i])	
			{
				p = insertKey(ptr->data[i], data);
				if(ptr->data[i]->numKeys == MAX_KEYS)
				{
					struct inode *m = splitData(ptr->data[i]);	
					for (int j = ++ptr->numKeys; j > i; j--)
					{
						ptr->keys[j] = ptr->keys[j-1];	
						ptr->data[j] = ptr->data[j-1];	
					}
					ptr->keys[i] = m->keys[0];	
					ptr->data[i] = m->data[0];
					ptr->data[i+1] = m->data[1];
				}
				break;
			}
		}

		if(p == -1)
		{
			p = insertKey(ptr->data[ptr->numKeys], data);

			if(ptr->data[ptr->numKeys]->numKeys == MAX_KEYS)
			{
				struct inode *m = splitData(ptr->data[ptr->numKeys]);	
				ptr->keys[ptr->numKeys++] = m->keys[0];	
				if(ptr->numKeys == 0)
					ptr->data[0] = m->data[0];
				ptr->data[ptr->numKeys] = m->data[1];
			}
		}
	}

	if(ptr->numKeys == MAX_KEYS)
		ptr = split(ptr);	

	return ptr;
}


struct inode *deleteElement(struct inode *ptr, int val)
{
	if(ptr->is_leaf)
	{
		int dataNodePos = getDataNodePos(ptr, val);
		int indexNodePos = dataNodePos > 0 ? dataNodePos-1 : dataNodePos;

		struct dnode *d = ptr->data[dataNodePos];
		int dataNodeInd = getPos(d, val);

		if(dataNodeInd == -1) // data not exist
			return ptr;

		deleteKey(d, dataNodeInd);

		if(indexNodePos != dataNodePos)
			ptr->keys[indexNodePos] = d->keys[0];

		if(d->numKeys < floor((MAX_KEYS-1) / 2))
			ptr = balanceData(ptr, dataNodePos);

		if(ptr->numKeys < floor((MAX_KEYS-1) / 2))
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

	for(int i = 0; i < ptr->numKeys; i++)
	{
		if(ptr->keys[i] > val)
			return deleteElement(ptr->children[i], val);
	}

	return deleteElement(ptr->children[ptr->numKeys], val);
}


int main()
{
	int data;
	int option;

	for (int i = 1; i < 10; i++)
		root = insert(root, i*10);

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
				if(root == NULL)
				{
					printf("Index is empty\n");
					continue;
				}

				printf("Index is :\n");
				displayIndex(root, 1);
				
				printf("Data is :\n");
				displayData(data_root);
				printf("\n\n");
				/* printf("Inorder Traversal is: "); */
				/* inorder(root); */
				/* printf("\n"); */
				break;
			case 4:
				printf("Enter the value to be searched : ");
				scanf("%d", &data);
				printf("Value position is: %d\n", search(root, data));
				break;
			case 5:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
