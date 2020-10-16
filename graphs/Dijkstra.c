#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

#define MAX 8
#define INF 9999

/* Undirected */
/* int adj[MAX][MAX] = { */
/* 	{ 0, 0, 0, 0, 0, 0, 0, 0 }, */
/* 	{ 0, 0, 0, 0, 0, 2, 6, 0 }, */
/* 	{ 0, 0, 0, 0, 4, 4, 0, 0 }, */
/* 	{ 0, 0, 0, 0, 0, 1, 0, 2 }, */
/* 	{ 0, 0, 4, 0, 0, 0, 0, 4 }, */
/* 	{ 0, 2, 4, 1, 0, 0, 3, 0 }, */
/* 	{ 0, 6, 0, 0, 0, 3, 0, 4 }, */
/* 	{ 0, 0, 0, 2, 4, 0, 4, 0 } */
/* }; */

/* Directed */
int adj[MAX][MAX] = {
	{ 0, 0, 4, 1, 0, 0, 0, 0 },
	{ 3, 0, 5, 0, 0, 0, 3, 0 },
	{ 0, 1, 0, 0, 0, 1, 0, 0 },
	{ 0, 4, 0, 0, 0, 4, 0, 0 },
	{ 0, 0, 7, 0, 0, 0, 2, 0 },
	{ 0, 6, 0, 9, 0, 0, 6, 2 },
	{ 0, 0, 0, 0, 0, 4, 0, 0 },
	{ 0, 0, 0, 0, 0, 4, 0, 0 }
};

int cost[MAX][MAX];

int visited[MAX], distance[MAX], pred[MAX];

void display(int source)
{
	printf("Source: %c\n", source+65);
	for(int i = 0; i < MAX; i++)
	{
		if(distance[i] == INF)
			continue;

		printf("Distance to node: %c - %d ", i+65, distance[i]);		

		printf("( ");
		int p = i;
		printf("%c", p+65);

		while(p != source)
		{
			printf(" %c", pred[p]+65);
			p = pred[p];
		} ;
		printf(" )\n");
	}
}

void dijksta(int source)
{
	for(int i = 0; i < MAX; i++)
	{
		for(int j = 0; j < MAX; j++)
		{
			if(adj[i][j] == 0)
				cost[i][j] = INF;
			else
				cost[i][j] = adj[i][j];
		}
	}

	for(int i = 0; i < MAX; i++)
	{
		visited[i] = 0;
		distance[i] = cost[source][i];
		pred[i] = source; 
	}

	int node = source;
	visited[source] = 1;
	distance[source] = 0;
	int count = 1;

	while(count < MAX-1)
	{
		int min_distance = INF;

		for(int i = 0; i < MAX; i++)
		{
			if(distance[i] < min_distance && !visited[i])
			{
				min_distance = distance[i];
				node = i;
			}

			visited[node] = 1;
			for(int j = 0; j < MAX; j++)
			{
				if(min_distance + cost[node][j] < distance[j])
				{
					distance[j] = min_distance + cost[node][j];
					pred[j] = node;
				}
			}
		}

		count++;
	}

}

int main()
{
	dijksta(1);	
	display(1);

	return 0;
}
