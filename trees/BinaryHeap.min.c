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
		printf("%d", heap[0]);
	}
	else
	{
		int num = pow(2, lvl);
		int parentNum = pow(2, lvl-1);

		for (int i = parentNum; i < num; i++)
		{
			int p1 = 2*i;
			int p2 = 2*i+1;
			pad(num);
			printf("%d", heap[p1-1]);
			pad(num);
			printf("%d", heap[p2-1]);
		}
	}

	if(lvl < (int) floor(log2(n)))
		return display(n, ++lvl);

	printf("\n");
}

void insert(int val, int pos)
{
	heap[pos-1] = val;	

	while(pos > 1)
	{
		int par = pos / 2;

		if(heap[pos-1] >= heap[par-1])
			break;
		else
		{
			int temp = heap[par-1];
			heap[par-1] = heap[pos-1];
			heap[pos-1] = temp;
			pos = par;
		}
	}
}

void deleteElement(int n)
{
	int last = heap[n-1];
	heap[n-1] = INT_MAX;

	int ptr = 1;
	int left = 2;
	int right = 3;

	heap[ptr-1] = last;
	while(left <= n)
	{
		if(heap[ptr-1] <= heap[left-1] && heap[ptr-1] <= heap[right-1])
			return;

		int temp = heap[ptr-1];
		if(heap[right-1] >= heap[left-1])
		{
			heap[ptr-1] = heap[left-1];
			heap[left-1] = temp;
			ptr = left;
		}
		else
		{
			heap[ptr-1] = heap[right-1];
			heap[right-1] = temp;
			ptr = right;
		}

		left = 2*(ptr+1);
		right = left;
	}
}

int main()
{
	int data;
	int option;
	int n = 0;

	for (int i = 0; i < NUM_KEYS; i++)
		heap[i] = INT_MAX;	

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
				deleteElement(n);
				n--;
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
