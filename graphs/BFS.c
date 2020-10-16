#include <stdio.h>
#define MAX 7

void breadth_first_search(int adj[][MAX], int visited[], int start)
{ 
	int queue[MAX], rear = -1, front = -1, i;
   	queue[++rear] = start;
   	visited[start] = 1;
	
	int orig[MAX];
	orig[rear] = -1;

	while(rear != front)
	{
		start = queue[++front];
		printf("%c ", start + 65);

		for(i = 0; i < MAX; i++)
		{
			if(adj[start][i] == 1 && visited[i] == 0)
			{
				queue[++rear] = i;
				orig[rear] = start;
				visited[i] = 1;
			}
		}
	}

	int end = 5;
	printf("\nShortest path: ");
	for (int i = MAX-1; i >= 0; i--)
	{
		if(queue[i] == end)
		{
			printf("%c ", queue[i] + 65);	
			end = orig[i];
		}
	}
	printf("\n");
}

int main()
{
	int visited[MAX] = {0};
	int adj[MAX][MAX] = {
		{0, 1, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
	};


	/* printf("\n Enter the adjacency matrix: "); */

	/* for(int i = 0; i < MAX; i++) */
	/*     for(int j = 0; j < MAX; j++) */
	/* 		scanf("%d", &adj[i][j]); */


	printf("BFS Traversal: ");
	breadth_first_search(adj, visited, 0);
	printf("\n");

	return 0;
}
