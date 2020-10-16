#include <stdio.h>

#define MAX 7

int n; 
// adj[MAX][MAX];

/* #define MAX 5 */
/* int adj[MAX][MAX] = { */
/* 	{0, 0, 1, 0, 0}, */
/* 	{0, 0, 0, 0, 0}, */
/* 	{0, 0, 0, 1, 1}, */
/* 	{0, 1, 0, 0, 0}, */
/* 	{0, 1, 0, 0, 0} */
/* }; */

int adj[MAX][MAX] = {
	{0, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0},
};

int front = -1, rear = -1, queue[MAX];

void create_graph(void);
void display();
void insert_queue(int);
int delete_queue(void);
int find_indegree(int);

int main()
{
	int topsort[MAX], indeg[MAX];
	/* create_graph(); */

	printf("\n The adjacency matrix is:");
	display();

	/*Find the in–degree of each node*/
	for(int node = 0; node < MAX; node++)
	{
		indeg[node] = find_indegree(node);
		if(indeg[node] == 0)
			insert_queue(node);
	}

	int j = 0, del_node = 0;
	while(front <= rear) /*Continue loop until queue is empty */
	{
		del_node = delete_queue();
		topsort[j] = del_node; /*Add the deleted node to topsort*/
		j++;

		/*Delete the del_node edges */
		for(int node = 0; node < MAX; node++)
		{
			if(adj[del_node][node] == 1)
			{
				adj[del_node][node] = 0;
				indeg[node] = indeg[node] - 1;

				if(indeg[node] == 0)
					insert_queue(node);
			}
		}
	}

	printf("The topological sorting can be given as :\n");

	for(int node = 0; node < MAX; node++)
		printf("%c ",topsort[node] + 65);
}

void create_graph()
{
	int max_edges, org, dest;

	printf("\n Enter the number of vertices: ");
	scanf("%d", &n);
	max_edges = n*(n - 1);

	for(int i = 1; i <= max_edges; i++)
	{
		printf("\n Enter edge %d(0 to quit): ", i);
		scanf("%d %d", &org, &dest);

		if((org == 0) && (dest == 0))
			break;

		if(org > n || dest > n || org <= 0 || dest <= 0)
		{
			printf("\n Invalid edge");
			i--;
		}
		else
			adj[org][dest] = 1;
	}
}

void display()
{
	for(int i = 0; i < MAX; i++)
	{
		printf("\n");

		for(int j = 0; j < MAX; j++)
			printf("%3d", adj[i][j]);
	}
	printf("\n");
}

void insert_queue(int node)
{
	if(rear == MAX-1)
		printf("\n OVERFLOW ");
	else
	{
		if(front == -1) /*If queue is initially empty */
			front=0;

		queue[++rear] = node;
	}
}

int delete_queue()
{
	if(front == -1 || front > rear)
	{
		printf("\n UNDERFLOW ");

		return -1;
	}
	else
		return queue[front++];
}

int find_indegree(int node)
{
	int in_deg = 0;

	for(int i = 0; i < MAX; i++)
	{
		if(adj[i][node] == 1)
			in_deg++;
	}

	return in_deg;
}
