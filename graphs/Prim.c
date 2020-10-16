#include <stdio.h>
#include <limits.h>

#define MAX 8

/* int adj[MAX][MAX] = { */
/* 		{ 0, 2, 0, 6, 0 }, */
/* 		{ 2, 0, 3, 8, 5 }, */
/* 		{ 0, 3, 0, 0, 7 }, */
/* 		{ 6, 8, 0, 0, 9 }, */
/* 		{ 0, 5, 7, 9, 0 } */ 
/* 	}; */

int adj[MAX][MAX] = {
		{ 0, 8, 8, 0, 6, 0, 0, 0 },
		{ 8, 0, 9, 0, 0, 0, 0, 0 },
		{ 8, 9, 0, 0, 7, 7, 9, 0 },
		{ 0, 0, 0, 0, 0, 8, 0, 8 },
		{ 6, 0, 7, 0, 0, 0, 0, 0 },
		{ 0, 0, 7, 8, 0, 0, 0, 4 },
		{ 0, 0, 9, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 8, 0, 4, 0, 0 },
	};

int mst_matrix[MAX][MAX];

void readmatrix()
{
	int n;

	printf("\n Enter the number of nodes in the Graph : ");
	scanf("%d", &n);
	printf("\n Enter the adjacency matrix of the Graph");

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &adj[i][j]);
}

int spanningtree(int src)
{
	int visited[MAX], d[MAX], parent[MAX];

	for(int i = 0; i < MAX; i++)
	{
		d[i] = adj[src][i];
		visited[i] = 0;
		parent[i] = src;
	}

	visited[src] = 1;

	int min, cost = 0;
	for(int i = 0, u = 0; i < MAX-1; i++)
	{
		min = INT_MAX;
		
		for(int j = 0; j < MAX; j++)
		{
			if(visited[j] == 0 && d[j] != 0 && d[j] < min)
			{
				min = d[j];
				u = j;
			}
		}

		visited[u] = 1;
		cost += d[u];
		mst_matrix[parent[u]][u] = d[u];
		mst_matrix[u][parent[u]] = d[u];
			 
		for(int v = 0; v < MAX; v++)
		{
			if(visited[v] == 0 && adj[u][v] != 0 && (d[v] == 0 || adj[u][v] < d[v]))
			{
				d[v] = adj[u][v];
				parent[v] = u;
			}
		}
	}
			 
	return cost;
}
				 
void display(int cost)
{
	printf("\nMininum Spanning Matrix:\n\n ");
	for (int i = 0; i < MAX; i++)
		printf(" %c", i+65);

	for (int i = 0; i < MAX; i++)
	{
		printf("\n%c", i+65);
		for (int j = 0; j < MAX; j++)
			printf(" %d", mst_matrix[i][j]);
	}

	printf("\n\nThe Total cost of the Minimum Spanning Tree is : %d", cost);
}
				 
int main()
{
	int source, treecost;
	/* readmatrix(); */
	printf("\n Enter the Source : ");
	scanf("%d", &source);
	treecost = spanningtree(source);
	display(treecost);
				 
	return 0;
}
