#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

#define MAX 18

struct edge
{
	char src;
	char dst;
	int weight;
};

char forest[MAX][MAX];
struct edge* mst[MAX-1];

struct edge* queue[MAX * MAX];
int n = 0;
int head = 0;


/* int adj[MAX][MAX] = { */
/* 	{ 0, 7, 6, 1, 0, 0 }, */
/* 	{ 7, 0, 8, 0, 0, 0 }, */
/* 	{ 6, 8, 0, 5, 3, 0 }, */
/* 	{ 1, 0, 5, 0, 4, 5 }, */
/* 	{ 0, 0, 3, 4, 0, 2 }, */
/* 	{ 0, 0, 0, 5, 2, 0 }, */
/* }; */

int adj[MAX][MAX] = {
	{ 0, 3, 7, 0, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 6, 0, 4, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 7, 0, 0, 2, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5, 8, 0, 0, 0, 0 },
	{ 0, 0, 0, 8, 0, 0, 6, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0, 0, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 9, 0, 0, 0, 7, 3, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 5, 0, 0, 0, 0, 0, 7, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 9, 0, 6, 7 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 0, 6, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 7, 0, 0 },
};

/* int adj[MAX][MAX] = { */
/* 		{ 0, 4, 0, 0, 0, 0, 0, 8, 0 }, */
/* 		{ 4, 0, 8, 0, 0, 0, 0, 11, 0 }, */
/* 		{ 0, 8, 0, 7, 0, 4, 0, 0, 2 }, */
/* 		{ 0, 0, 7, 0, 9, 14, 0, 0, 0 }, */
/* 		{ 0, 0, 0, 9, 0, 10, 0, 0, 0 }, */
/* 		{ 0, 0, 4, 14, 10, 0, 2, 0, 0 }, */
/* 		{ 0, 0, 0, 0, 0, 2, 0, 1, 6}, */
/* 		{ 8, 11, 0, 0, 0, 0, 1, 0, 7 }, */
/* 		{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }, */
/* 	}; */

struct edge *pop()
{
	if(head == n)
	{
		printf("UNDERFLOW\n");
		exit(0);
	}

	return queue[head++];
}

void insert(char src, char dst, int weight)
{
	if(weight == 0)
		return;

	struct edge *e = (struct edge*)malloc(sizeof(struct edge));
	e->src = src;
	e->dst = dst;
	e->weight = weight;

	int i = 0;
	for(; i < n; i++)
	{
		if(queue[i]->weight > weight)
			break;
	}

	for(int j = n; j > i; j--)
		queue[j] = queue[j-1];	
	
	queue[i] = e;
	n++;
}

void display(int matrix[MAX][MAX])
{
	printf("\nMininum Spanning Matrix:\n\n ");
	for(int i = 0; i < MAX; i++)
		printf(" %2c", i+65);

	for(int i = 0; i < MAX; i++)
	{
		printf("\n%c", i+65);
		for(int j = 0; j < MAX; j++)
			printf(" %2d", matrix[i][j]);
	}

	printf("\n\nQueue:\n");
	for(int i = 0; i < n; i++)
	{
		struct edge *e = queue[i];
		printf("%c - %c weight: %d\n", e->src, e->dst, e->weight);	
	}

	printf("\nForest:\n");
	for(int i = 0; i < MAX; i++)
	{
		char *vertex_set = forest[i];
		printf("{");
		for(int j = 0; j < MAX; j++)
		{
			if(vertex_set[j] == 0)
				break;
			printf("%c,", vertex_set[j]);			
		}
		printf("}");
	}

	printf("\n\nMST:\n");
	for(int i = 0; i < MAX-1; i++)
	{
		struct edge *e = mst[i];
		printf("%d - %d weight: %d\n", e->src-65, e->dst-65, e->weight);	
	}
}

void read_matrix()
{
	for(int i = 0; i < MAX; i++)
	{
		forest[i][0] = i+65;
		for(int j = i; j < MAX; j++)
			insert(i+65, j+65, adj[i][j]);
	}
}

int forest_by_vertex(char v)
{
	for(int i = 0; i < MAX; i++)
	{
		for(int j = 0; j < MAX; j++)
		{
			if(forest[i][j] == v)
				return i;
		}
	}

	return -1;
}

void kruskal()
{
	printf("\n\n\n");
	int mst_ind = 0;
	while(head != n)
	{
		struct edge *e = pop();
		int f1 = forest_by_vertex(e->src);
		int f2 = forest_by_vertex(e->dst);

		if(f1 == f2)
			continue;

		mst[mst_ind++] = e;

		// union
		for(int i = 0; i < MAX; i++)
		{
			if(forest[f1][i] == 0)
			{
				for(int j = 0; forest[f2][j] != 0; j++)
				{
					forest[f1][i + j] = forest[f2][j];
					forest[f2][j] = 0;
				}

				break;
			}
		}
	}
	display(adj);
}
				 
int main()
{
	read_matrix();
	kruskal();
				 
	return 0;
}
