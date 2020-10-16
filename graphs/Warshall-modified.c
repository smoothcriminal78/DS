#include <stdio.h>
#define MAX 4
#define INFINITY 9999

// Modified to obtain matrix that gives the shortest paths between the nodes in a graph G

/* int adj[MAX][MAX] = { */
/* 	{ 0, 5, 0, 10, }, */
/* 	{ 0, 0, 3, 0, }, */
/* 	{ 0, 0, 0, 1, }, */
/* 	{ 0, 0, 0, 0, }, */
/* }; */

int adj[MAX][MAX] = {
	{ 0, 3, 3, 0, },
	{ 0, 0, 0, 1, },
	{ 0, 3, 0, 0, },
	{ 2, 0, 5, 0, },
};

void read(int mat[MAX][MAX], int n);
void display(int mat[MAX][MAX], int n);

int main()
{
	int Q[MAX][MAX];

	/* printf("\n Enter the number of nodes in the graph : "); */
	/* scanf("%d", &n); */
	/* printf("\n Enter the adjacency matrix : "); */
	/* read(adj, n); */

	printf("\n The adjacency matrix is : ");
	display(adj, MAX);

	for(int i = 0; i < MAX; i++)
	{
	    for(int j = 0; j < MAX; j++)
	    {
	   	 if(adj[i][j] == 0)
			 Q[i][j] = INFINITY;
	   	 else
	   		 Q[i][j] = adj[i][j];
	    }
	}

	for(int k = 0; k < MAX; k++)
	{
		for(int i = 0; i < MAX; i++)
		{
			for(int j = 0; j < MAX; j++)
			{
			    if(Q[i][j] <= Q[i][k] + Q[k][j])
					Q[i][j] = Q[i][j];
			    else
					Q[i][j] = Q[i][k] + Q[k][j];
			}
		}

		printf("\n\nQ (%d) \n", k);
		display(Q, MAX);
	}

	return 0;
}

void read(int mat[MAX][MAX], int n)
{
	for(int i = 0; i < MAX; i++)
	{
		for(int j = 0; j < MAX; j++)
		{
			printf("\n mat[%d][%d] = ", i, j);
			scanf("%d", &mat[i][j]);
		}
	}
}

void display(int mat[MAX][MAX], int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("\n");
		for(int j = 0; j < n; j++)
			printf("%d\t", mat[i][j]);
	}
}
