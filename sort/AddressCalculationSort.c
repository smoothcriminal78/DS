#include <stdio.h>
#include <stdlib.h>

#define MAX 30

struct node
{
	int data;
	struct node *next;
} *nodes[10] = {NULL};

struct node *insert(struct node *start, int num)
{
	struct node *ptr, *new_node;
	ptr = start;
	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = num;
	new_node->next = NULL;

	if(start == NULL)
		start = new_node;
	else
	{
		//insert the new node at its right position
		while((ptr->next != NULL) && (ptr->next->data <= num))
			ptr = ptr->next;
		
		if(new_node->data < ptr->data)
		{
			new_node->next = ptr;
			start = new_node;
		}
		else
		{
			new_node->next = ptr->next;
			ptr->next = new_node;
		}
	}
		
	return start;
}
		
void addr_calc_sort(int arr[], int n)
{
	for(int i = 0, pos = 0; i < n; i++)
	{
		pos = arr[i] / 10;
		nodes[pos] = insert(nodes[pos], arr[i]);
	}

	for(int i = 0, j = 0; i < 10; i++)
	{
		while(nodes[i] != NULL)
		{
			arr[j++] = nodes[i]->data;
			nodes[i] = nodes[i]->next;
		}
	}

	printf("\nSorted output is: ");
	for(int i = 0; i < n; i++)
		printf("%d\t", arr[i]);
}

int main()
{
	int arr[MAX], n;

	/* printf("\n Enter the number of elements : "); */
	/* scanf("%d",&n); */
	/* printf("\n Enter the elements : "); */
	/* for(int i = 0; i < n; i++) */
	/* 	scanf("%d", &arr[i]); */

	for(int i = MAX-1; i >= 0; i--)
		arr[i] = i;	

	addr_calc_sort(arr, MAX);

	return 0;
}
