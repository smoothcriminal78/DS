#include <stdio.h>
#define MAX 4

void read(int mat[MAX][MAX]);
void display(int mat[MAX][MAX]);
void mul(int mat[MAX][MAX]);

int main()
{
	int P[MAX][MAX];

	int adj[MAX][MAX] = {
		{ 0, 5, 0, 10, },
		{ 0, 0, 3, 0, },
		{ 0, 0, 0, 1, },
		{ 0, 0, 0, 0, },
	};

	/* printf("\n Enter the number of nodes in the graph : "); */
	/* scanf("%d", &n); */
	/* printf("\n Enter the adjacency matrix : "); */
	/* read(adj, n); */

	printf("\n The adjacency matrix is : ");
	display(adj);

	for(int i = 0; i < MAX; i++)
	{
	    for(int j = 0; j < MAX; j++)
	    {
			if(adj[i][j] == 0)
				P[i][j] = 0;
			else
				P[i][j] = 1;
	    }
	}

	for(int k = 0; k < MAX; k++)
	{
	    for(int i = 0; i < MAX; i++)
	    {
			for(int j = 0; j < MAX; j++)
				P[i][j] = P[i][j] | (P[i][k] & P[k][j]);
	    }

		printf("\n The Path (%d) Matrix is :", k);
		display(P);
	}


	return 0;
}

void read(int mat[MAX][MAX])
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

void display(int mat[MAX][MAX])
{
	for(int i = 0; i < MAX; i++)
	{
		printf("\n");
		for(int j = 0; j < MAX; j++)
			printf("%d\t", mat[i][j]);
	}
}
