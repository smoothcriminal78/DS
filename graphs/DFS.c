#include <stdio.h>

#define MAX 5

void depth_first_search(int adj[][MAX],int visited[],int start)
{
	int stack[MAX];
	int top = -1, i;

	printf("%c ",start + 65);
	visited[start] = 1;
	stack[++top] = start;

	int orig[MAX];
	orig[top] = -1;

	while(top != -1)
	{
		start = stack[top];

		for(i = 0; i < MAX; i++)
		{
			if(adj[start][i] && visited[i] == 0)
			{
				stack[++top] = i;
				orig[top] = start;
				printf("%c ", i + 65);
				visited[i] = 1;

				break;
			}
		}

		if(i == MAX)
			top--;
	}

	printf("\n ");
	for (int i = 0; i < MAX; i++)
		printf("%d ", stack[i]);
	printf("\n");
	for (int i = 0; i < MAX; i++)
		printf("%d ", orig[i]);
		

	int end = 4;
	printf("\nShortest path: ");
	for (int i = MAX-1; i >= 0; i--)
	{
		if(stack[i] == end)
		{
			printf("%c ", stack[i] + 65);	
			while(i != 0)
				printf("%c ", orig[i--] + 65);	

			break;
		}
	}
	printf("\n");
}

int main()
{
	int adj[MAX][MAX] = {
	    {0, 0, 1, 0, 0},
	    {0, 0, 0, 0, 0},
	    {0, 0, 0, 1, 1},
	    {0, 1, 0, 0, 0},
	    {0, 1, 0, 0, 0}
	};
	int visited[MAX] = {0};

	/* printf("\n Enter the adjacency matrix: "); */

	/* for(int i = 0; i < MAX; i++) */
	/* 	for(int j = 0; j < MAX; j++) */
	/* 		scanf("%d", &adj[i][j]); */

	printf("DFS Traversal: ");
	depth_first_search(adj, visited, 0);
	printf("\n");

	return 0;
}
