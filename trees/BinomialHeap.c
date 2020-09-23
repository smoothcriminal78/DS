#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <limits.h> 

struct node {
	int val;
	int degree;
	struct node *child;
	struct node *parent;
	struct node *sibling;
};

struct heap {
	struct node *head;
};

void node_display(struct node *n)
{
	printf("--------\n");
	printf("P: %d\n", n->parent != NULL ? n->parent->val : -1);
	printf("V: %d\n", n->val);
	printf("D: %d\n", n->degree);
	printf("C: %d\n", n->child != NULL ? n->child->val : -1);
	printf("S: %d\n", n->sibling != NULL ? n->sibling->val : -1);
	printf("--------\n");

	if(n->child != NULL)
		node_display(n->child);

	if(n->sibling != NULL)
		node_display(n->sibling);
}

void heap_display(struct heap* h)
{
	node_display(h->head);
}

struct heap* heap_create()
{
	struct heap *h = (struct heap*)malloc(sizeof(struct heap));
	h->head = NULL;

	return h;
}

// Makes Y the new head of the linked list of node Z’s children in O(1) time.
void tree_link(struct node *y, struct node *z)
{
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

struct node *heap_merge(struct heap *h1, struct heap *h2)
{
	if(h1->head == NULL) return h2->head;
	if(h2->head == NULL) return h1->head;

	struct node *head, *tail;

	struct node *h1It = h1->head;
	struct node *h2It = h2->head;

	if(h1It->degree <= h2It->degree)
	{
		head = h1->head;
		h1It = h1It->sibling;
	}
	else
	{
		head = h2->head;
		h2It = h2It->sibling;
	}
	tail = head;

	while(h1It != NULL && h2It != NULL)
	{
		if(h1It->degree <= h2It->degree)
		{
			tail->sibling = h1It;
			h1It = h1It->sibling;
		}
		else
		{
			tail->sibling = h2It;
			h2It = h2It->sibling;
		}

		tail = tail->sibling;
	}

	tail->sibling = (h1It != NULL) ? h1It : h2It;

	return head;
}

// Links together binomial trees whose roots have the same degree
struct heap *heap_union(struct heap *h1, struct heap *h2)
{
	struct heap *h = heap_create();
	h->head = heap_merge(h1, h2);

	free(h1);
	free(h2);

	if(h->head == NULL)
		return h;

	struct node *prev = NULL;
	struct node *ptr = h->head;
	struct node *next = ptr->sibling;

	while(next != NULL)
	{
		/* printf("Union"); */
		/* printf(" prev: %d", prev != NULL ? prev->val : -1); */
		/* printf(" ptr: %d", ptr != NULL ? ptr->val: -1); */
		/* printf(" next: %d", next != NULL ? next->val : -1); */
		/* printf("\n"); */

		if(ptr->degree != next->degree || (next->sibling != NULL && next->sibling->degree == ptr->degree))
		{
			prev = ptr;
			ptr = next;
		}
		else if(ptr->val <= next->val)
		{
			ptr->sibling = next->sibling;
			tree_link(next, ptr);
		}
		else
		{
			if(prev == NULL)
				h->head = next;
			else
				prev->sibling = next;

			tree_link(ptr, next);
			ptr = next;
		}
		next = ptr->sibling;
	}
	
	return h;
}

struct heap *heap_insert(struct heap *h, struct node *x)
{
	struct heap *h_ = heap_create();
	x->parent  = NULL;
	x->child = NULL;
	x->sibling = NULL;
	x->degree = 0;
	h_->head = x;

	return heap_union(h, h_);
}

struct node *heap_min(struct heap* h)
{
	struct node *y = NULL, *x = h->head;
	int min = INT_MAX;

	while(x != NULL)
	{
		if(x->val < min)
		{
			min = x->val;
			y = x;
		}
		x = x->sibling;
	}

	return y; 
}

void heap_decrease(struct heap *h, struct node *x, int k)
{
	if(x->val < k)
		printf("Error\n");

	x->val = k;
	struct node *ptr = x;
	struct node *par = ptr->parent;

	while(par != NULL && ptr->val < par->val)
	{
		int temp = ptr->val;
		ptr->val = par->val;
		par->val = temp;

		ptr = par;
		par = ptr->parent;
	}
}

struct heap *heap_remove(struct heap *h, struct node *n, struct node *prev)
{
	if(n == h->head)
		h->head = n->sibling;
	else
		prev->sibling = n->sibling;

	struct node *new_head = NULL;
	struct node *child = n->child;

	while(child != NULL)
	{
		struct node *next = child->sibling;
		child->sibling = new_head;
		child->parent = NULL;
		new_head = child;
		child = next;
	}

	struct heap *temp = heap_create();
	temp->head = new_head;

	return heap_union(h, temp);
}


struct heap *extract_min(struct heap* h)
{
	if(h->head == NULL)
		return NULL;

	struct node *min = h->head;
	struct node *min_prev = NULL;
	struct node *next = min->sibling;
	struct node *next_prev = min;

	while(next != NULL)
	{
		if(next->val < min->val)
		{
			min = next;
			min_prev = next_prev;
		}

		next_prev = next;
		next = next->sibling;
	}

	h = heap_remove(h, min, min_prev);

	return h;
}


struct heap *heap_delete(struct heap *h, struct node *x)
{
	heap_decrease(h, x, INT_MIN);

	return extract_min(h);
}

int main()
{
	int val;
	int option;

	struct heap *h = heap_create();
	struct node *n, *saved = NULL;

	/* for(int i = 1; i < 16; i++) */
	/* { */
	/* 	n = (struct node*)malloc(sizeof(struct node)); */
	/* 	n->val = i*10; */
	/* 	h = heap_insert(h, n); */
	/* 	if(i == 3) */
	/* 		saved = n; */
	/* } */

	while(1)
	{
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Display\n");
		printf("4.Node save\n");
		printf("5.Min\n");
		printf("6.Min Extract\n");
		printf("7.Decrease\n");
		printf("8.Quit\n");
		printf("Enter your option : ");
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Enter the value to be inserted : ");
				n = (struct node*)malloc(sizeof(struct node));
				scanf("%d", &n->val);
				h = heap_insert(h, n);
				break;
			case 2:
				if(saved != NULL)
				{
					h = heap_delete(h, saved);
					printf("Deleted!\n");
				}
				else
					printf("Save the node first!\n");
				break;
			case 3:
				printf("Tree is :\n");
				heap_display(h);
				break;
			case 4:
				if(n != NULL)
				{
					saved = n;
					printf("Node saved!\n");
					node_display(saved);
				}
				else
					printf("Node is NULL\n");
				break;
			case 5:
				printf("Min value: %d\n", heap_min(h)->val);
				break;
			case 6:
				printf("Extracting node with Min value\n");
				h = extract_min(h);
				break;
			case 7:
				if(saved != NULL)
				{
					printf("Enter the value: ");
					scanf("%d", &val);
					printf("\nDecreasing node:\n");
					node_display(saved);
					heap_decrease(h, saved, val);
				}
				else
					printf("Save the node first!\n");
				break;
			case 8:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
