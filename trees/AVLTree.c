#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum { FALSE ,TRUE } bool;

struct node
{
	int val;
	int balance;
	struct node *left_child;
	struct node *right_child;
};


struct node* search(struct node *ptr, int data)
{
	if(ptr!=NULL)
	{
		if(data < ptr->val)
			ptr = search(ptr->left_child, data);
		else if(data > ptr->val)
			ptr = search(ptr->right_child, data);
	}

	return ptr;
}

int Height(struct node *tree)
{
	int leftheight, rightheight;

	if(tree==NULL)
		return 0;
	else
	{
		leftheight = Height(tree->left_child);
		rightheight = Height(tree->right_child);

		if(leftheight > rightheight)
			return (leftheight + 1);
		else
			return (rightheight + 1);
	}
}

struct node *insert(int data, struct node *ptr, bool *ht_inc)
{
	struct node *aptr;
	struct node *bptr;

	if(ptr==NULL)
	{
		ptr = (struct node*) malloc (sizeof(struct node));
		ptr->val = data;
		ptr->left_child = NULL;
		ptr->right_child = NULL;
		ptr->balance = 0;
		*ht_inc = TRUE;

		return ptr;
	}

	if(data < ptr->val)
	{
		ptr->left_child = insert(data, ptr->left_child, ht_inc);

		if(*ht_inc==TRUE)
		{
			switch(ptr->balance)
			{
				case -1: /* Right heavy */
					ptr->balance = 0;
					*ht_inc = FALSE;
					break;
				case 0: /* Balanced */
					ptr->balance = 1;
					break;
				case 1: /* Left heavy */
					aptr = ptr->left_child;
					if(aptr->balance == 1)
					{
						printf("Left to Left Rotation\n");
						ptr->left_child = aptr->right_child;
						aptr->right_child = ptr;
						ptr->balance = 0;
						aptr->balance=0;
						ptr = aptr;
					}
					else
					{
						printf("Left to right rotation\n");
						bptr = aptr->right_child;
						aptr->right_child = bptr->left_child;
						bptr->left_child = aptr;
						ptr->left_child = bptr->right_child;
						bptr->right_child = ptr;

						if(bptr->balance == 1)
							ptr->balance = -1;
						else
							ptr->balance = 0;
						if(bptr->balance == -1)
							aptr->balance = 1;
						else
							aptr->balance = 0;
						bptr->balance=0;
						ptr = bptr;
					}
					*ht_inc = FALSE;
			}
		}
	}

	if(data > ptr->val)
	{
		ptr->right_child = insert(data, ptr->right_child, ht_inc);

		if(*ht_inc==TRUE)
		{
			switch(ptr->balance)
			{
				case 1: /* Left heavy */
					ptr->balance = 0;
					*ht_inc = FALSE;
					break;
				case 0: /* Balanced */
					ptr->balance = -1;
					break;
				case -1: /* Right heavy */
					aptr = ptr->right_child;

					if(aptr->balance == -1)
					{
						printf("Right to Right Rotation\n");
						ptr->right_child= aptr->left_child;
						aptr->left_child = ptr;
						ptr->balance = 0;
						aptr->balance=0;
						ptr = aptr;
					}
					else
					{
						printf("Right to Left Rotation\n");
						bptr = aptr->left_child;
						aptr->left_child = bptr->right_child;
						bptr->right_child = aptr;
						ptr->right_child = bptr->left_child;
						bptr->left_child = ptr;

						if(bptr->balance == -1)
							ptr->balance = 1;
						else
							ptr->balance = 0;
						if(bptr->balance == 1)
							aptr->balance = -1;
						else
							aptr->balance = 0;
						bptr->balance=0;
						ptr = bptr;
					} /*End of else*/
					*ht_inc = FALSE;
			}
		}
	}

	return ptr;
}


struct node *findSmallestElement(struct node *ptr)
{
	if((ptr == NULL) || (ptr->left_child == NULL))
		return ptr;
	else
		return findSmallestElement(ptr->left_child);
}


struct node *findLargestElement(struct node *ptr)
{
	if((ptr == NULL) || (ptr->right_child == NULL))
		return ptr;
	else
		return findLargestElement(ptr->right_child);
}


struct node *delete(int val, struct node *ptr)
{
	struct node *aptr, *bptr, *cptr;
	struct node *temp;

	if(ptr==NULL)
	{
		printf("\n The tree is empty ");
		return ptr;
	}
	else if (val < ptr->val)
	{
		ptr->left_child = delete(val, ptr->left_child);
		ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);

		if(ptr->balance == -2)
		{
			switch(ptr->right_child->balance)
			{
				case 1: /* L1 */
					printf("L1 rotation.\n");
					bptr = ptr->right_child;
					cptr = bptr->left_child;
					ptr->balance = Height(ptr->left_child) - Height(cptr->left_child);

					bptr->left_child = cptr->right_child;
					ptr->right_child = cptr->left_child;
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					cptr->right_child = bptr;
					cptr->left_child = ptr;
					cptr->balance = Height(cptr->left_child) - Height(cptr->right_child);

					ptr = cptr;
					break;
				case 0: /* L0 */
					printf("L0 rotation.\n");
					bptr = ptr->right_child;
					ptr->right_child = bptr->left_child;
					bptr->left_child = ptr;

					ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					ptr = bptr;
					break;
				case -1: /* L-1 */
					printf("L-1 rotation.\n");
					bptr = ptr->right_child;
					temp = bptr->left_child;
					bptr->left_child = ptr;
					ptr->right_child = temp;

					ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					ptr = bptr;
					break;
			}
		}
	}
	else if (val > ptr->val)
	{
		ptr->right_child = delete(val, ptr->right_child);
		ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);

		if(ptr->balance == 2)
		{
			switch(ptr->left_child->balance)
			{
				case 1: /* R1 */
					printf("R1 rotation.\n");
					bptr = ptr->left_child;
					temp = bptr->right_child;
					bptr->right_child = ptr;
					ptr->left_child = temp;

					ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					ptr = bptr;
					break;
				case 0: /* R0 */
					printf("R0 rotation.\n");
					bptr = ptr->left_child;
					ptr->left_child = bptr->right_child;
					bptr->right_child = ptr;

					ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					ptr = bptr;
					break;
				case -1: /* R-1 */
					printf("R-1 rotation.\n");
					bptr = ptr->left_child;
					cptr = bptr->right_child;
					ptr->balance = Height(cptr->right_child) - Height(ptr->right_child);

					bptr->right_child = cptr->left_child;
					ptr->left_child = cptr->right_child;
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					cptr->left_child = bptr;
					cptr->right_child = ptr;
					cptr->balance = Height(cptr->left_child) - Height(cptr->right_child);

					ptr = cptr;
					break;
			}
		}
	}
	else if (ptr->left_child && ptr->right_child)
	{
		temp = findLargestElement(ptr->left_child);
		ptr->val = temp->val;
		ptr->left_child = delete(temp->val, ptr->left_child);
		ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);

		if(ptr->balance == -2)
		{
			switch(ptr->right_child->balance)
			{
				case 1: /* L1 */
					printf("L1 rotation.\n");
					bptr = ptr->right_child;
					cptr = bptr->left_child;
					ptr->balance = Height(ptr->left_child) - Height(cptr->left_child);

					bptr->left_child = cptr->right_child;
					ptr->right_child = cptr->left_child;
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					cptr->right_child = bptr;
					cptr->left_child = ptr;
					cptr->balance = Height(cptr->left_child) - Height(cptr->right_child);

					ptr = cptr;
					break;
				case 0: /* L0 */
					printf("L0 rotation.\n");
					bptr = ptr->right_child;
					ptr->right_child = bptr->left_child;
					bptr->left_child = ptr;

					ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					ptr = bptr;
					break;
				case -1: /* L-1 */
					printf("L-1 rotation.\n");
					bptr = ptr->right_child;
					temp = bptr->left_child;
					bptr->left_child = ptr;
					ptr->right_child = temp;

					ptr->balance = Height(ptr->left_child) - Height(ptr->right_child);
					bptr->balance = Height(bptr->left_child) - Height(bptr->right_child);

					ptr = bptr;
					break;
			}
		}
	}
	else
	{
		if(ptr->left_child==NULL && ptr->right_child==NULL)
		{
			free(ptr);
			return NULL;
		}
		else if(ptr->left_child!=NULL)
		{
			ptr=ptr->left_child;
		}
		else
		{
			ptr=ptr->right_child;
		}
	}

	return ptr;
}


void display(struct node *ptr, int level)
{
	int i;
	if(ptr!=NULL)
	{
		display(ptr->right_child, level+1);
		printf("\n");

		for (i = 0; i < level; i++)
			printf(" ");

		printf("%d", ptr->val);
		display(ptr->left_child, level+1);
	}
}


void inorder(struct node *ptr)
{
	if(ptr!=NULL)
	{
		inorder(ptr->left_child);
		printf("%d(%d) ",ptr->val, ptr->balance);
		inorder(ptr->right_child);
	}
}


int main()
{
	bool ht_inc;
	int data;
	int option;
	struct node *root = (struct node *)malloc(sizeof(struct node));
	root = NULL;

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
					root = insert(data, root, &ht_inc);
				else
					printf("Duplicate value ignored\n");
				break;
			case 2:
				printf("Enter the value to be deleted : ");
				scanf("%d", &data);
				if(search(root, data) == NULL)
					printf("Value not found!\n");
				else
					root = delete(data, root);
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
