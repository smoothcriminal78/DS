#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <limits.h> 

#define NUM_KEYS (4096)

typedef enum { FALSE, TRUE } bool;

int heap[NUM_KEYS];

void pad(int n)
{
	for (int i = 0; i < (64/(n+1))-2; i++)
		printf(" ");
}

void display(int n, int lvl)
{
	printf("\n");
	if(lvl == 0)
	{
		if(n == 0)
		{
			printf("Tree is empty\n");
			return;
		}

		pad(1);
		printf("%d", heap[1]);
	}
	else
	{
		int num = pow(2, lvl);
		int parentNum = pow(2, lvl-1);

		for (int i = parentNum; i < num; i++)
		{
			int p1 = 2*i;
			int p2 = p1+1;
			pad(num);
			printf("%d", heap[p1]);
			pad(num);
			printf("%d", heap[p2]);
		}
	}

	if(lvl < (int) floor(log2(n)))
		return display(n, ++lvl);

	printf("\n");
}

void insert(int val, int pos)
{
	heap[pos] = val;	

	while(pos > 1)
	{
		int par = pos / 2;

		if(heap[pos] <= heap[par])
			break;
		else
		{
			int temp = heap[par];
			heap[par] = heap[pos];
			heap[pos] = temp;
			pos = par;
		}
	}
}

void deleteElement(int n)
{
	int last = heap[n];
	heap[n] = INT_MIN;

	int ptr = 1;
	int left = 2;
	int right = 3;

	heap[ptr] = last;
	while(left <= n)
	{
		if(heap[ptr] >= heap[left] && heap[ptr] >= heap[right])
			return;

		int temp = heap[ptr];
		if(heap[right] <= heap[left])
		{
			heap[ptr] = heap[left];
			heap[left] = temp;
			ptr = left;
		}
		else
		{
			heap[ptr] = heap[right];
			heap[right] = temp;
			ptr = right;
		}

		left = 2*ptr;
		right = left+1;
	}
}

int main()
{
	int data;
	int option;
	int n = 0;

	for (int i = 0; i < NUM_KEYS; i++)
		heap[i] = INT_MIN;	

	for (int i = 9; i > 0; i--)
	{
		n++;
		insert(i, n);	
	}

	while(1)
	{
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Display\n");
		printf("4.Quit\n");
		printf("Enter your option : ");
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Enter the value to be inserted : ");
				scanf("%d", &data);
				n++;
				insert(data, n);
				break;
			case 2:
				if(n > 0)
				{
					deleteElement(n);
					n--;
				}
				else
					printf("Tree is empty!\n");
				break;
			case 3:
				printf("Tree is :\n");
				display(n, 0);
				break;
			case 4:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
