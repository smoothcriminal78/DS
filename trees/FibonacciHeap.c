#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <limits.h> 

typedef enum { FALSE, TRUE } bool;

struct node {
	int val;
	int degree;
	bool mark;
	struct node *child;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct heap {
	int n;
	struct node *min;
};

void printArray(struct node *ARR[], int arr_sz)
{
	printf("Array: ");
	for (int i = 0; i < arr_sz; i++)
		printf("%d ", ARR[i] != NULL ? ARR[i]->val : -1);
	printf("\n");
}

void NodePrint(struct node *n)
{
	printf("-----\n");
	printf("P: %d\n", n->parent != NULL ? n->parent->val : -1);
	printf("V: %d\n", n->val);
	printf("D: %d\n", n->degree);
	printf("M: %d\n", n->mark);
	printf("C: %d\n", n->child != NULL ? n->child->val : -1);
	printf("L: %d\n", n->left != NULL ? n->left->val : -1);
	printf("R: %d\n", n->right != NULL ? n->right->val : -1);
	printf("-----\n");
}

void RowDisplay(struct node *n, struct node *beg)
{
	NodePrint(n);
	n = n->right;
	if(n->child != NULL)
		RowDisplay(n->child, n->child);
	if(n != beg)
		return RowDisplay(n, beg);
}

void heap_display(struct heap *h)
{
	if(h->min == NULL)
	{
		printf("Heap is empty!\n");
		return;
	}

	printf("Size of heap: %d\n", h->n);

	RowDisplay(h->min, h->min);
}

struct heap* heap_create()
{
	struct heap *h = (struct heap*)malloc(sizeof(struct heap));
	h->n = 0;
	h->min = NULL;

	return h;
}

struct heap* heap_insert(struct heap *h, struct node *x)
{
	x->degree = 0;
	x->parent = NULL;
	x->child = NULL;
	x->mark = FALSE;
	x->left = x->right = x;

	if(h->min != NULL)
	{
		struct node *temp = h->min->left;

		h->min->left = x;
		x->right = h->min;

		x->left = temp;
		temp->right = x;
	}

	if(h->min == NULL || x->val < h->min->val)
		h->min = x;

	h->n++;
	
	return h;
}

struct heap* node_insert(struct heap *h, struct node *x)
{
	struct node *temp;
	x->left = x->right = x;
	x->parent = NULL;

	if(h->min == NULL)
		h->min = x;
	else
	{
		temp = h->min->left;

		h->min->left = x;
		x->right = h->min;

		x->left = temp;
		temp->right = x;

		if(x->val < h->min->val)
			h->min = x;
	}

	return h;
}

struct heap *heap_union(struct heap *h1, struct heap *h2)
{
	struct heap *h_ = heap_create();
	h_->min = h1->min;

	struct node *temp = h_->min->right;
	h_->min->right = h2->min->right;
	h2->min->right->left = h_->min;
	temp->left = h2->min;
	h2->min->right = temp;

	if(h1->min == NULL || (h2->min != NULL && h2->min < h1->min))
		h1->min = h2->min;

	h_->n = h1->n + h2->n;

	free(h1);
	free(h2);

	return h_;
}

void heap_min(struct heap *h)
{
	if(h->min == NULL)
	{
		printf("Heap is empty!\n");
		return;
	}

	printf("Heap min : %d\n", h->min->val);
}

struct heap *link(struct heap *h, struct node *x, struct node *y)
{
	if(y->right != y)
	{
		y->left->right = y->right;
		y->right->left = y->left;
	}

	y->left = y->right = y;

	if(x->child != NULL)
	{
		struct node *temp = x->child->left;
		y->left = temp;
		temp->right = y;

		y->right = x->child;
		x->child->left = y;
	}

	x->child = y;
	y->parent = x;
	x->degree++;
	y->mark = FALSE;

	return h;
}


struct heap *consolidate(struct heap *h)
{
	int arr_sz = (int) (log2(h->n) / log2(1.618));
	struct node *ARR[arr_sz];

	for (int i = 0; i < arr_sz; i++)
		ARR[i] = NULL;

	struct node *x = h->min;
	struct node *ptr;

	while(1)
	{
		ptr = x;
		x = x->right;
		int deg = ptr->degree;
		while(ARR[deg] != NULL)
		{
			struct node *temp = ARR[deg];
			if(temp == ptr) goto end;

			if(ptr->val > temp->val)
			{
				temp = ptr;
				ptr = ARR[deg];
			}
			link(h, ptr, temp);

			ARR[deg] = NULL;
			deg++;
		}

		ARR[deg] = ptr;
	}

	end:

	h->min = NULL;

	for(int i = 0; i < arr_sz; i++)
	{
		if(ARR[i] != NULL)		
		{
			x = ARR[i];

			if(x != NULL)
				h = node_insert(h , x);
		}
	}

	return h;
}

struct node *extract_min(struct heap *h)
{
	struct node *x = h->min;

	if(x != NULL)
	{
		struct node *ptr = x->child;
		if(ptr != NULL)
		{
			struct node *next = ptr->right;
			do
			{
				h = node_insert(h, ptr);
				ptr = next;
				next = next->right;
			} while(ptr != x->child);
		}

		x->left->right = x->right;
		x->right->left = x->left;
	}

	if(x == x->right)
		h->min = NULL;
	else
	{
		h->min = x->right;
		consolidate(h);
	}

	h->n--;

	return x;
}

struct heap *cut(struct heap *h, struct node *ptr, struct node *par)
{
	if(ptr->right == ptr)
		par->child = NULL;
	else
		par->child = ptr->right;

	ptr->left->right = ptr->right;
	ptr->right->left= ptr->left;

	par->degree--;
	h = node_insert(h, ptr);
	ptr->parent = NULL;
	ptr->mark = FALSE;

	return h;
}

struct heap *cascading_cut(struct heap *h, struct node *ptr)
{
	struct node *par = ptr->parent;

	if(par != NULL)
	{
		if(ptr->mark == FALSE)
			ptr->mark = TRUE;
		else
		{
			cut(h, ptr, par);
			cascading_cut(h, par);
		}
	}

	return h;
}

struct heap *node_decrease(struct heap *h, struct node *ptr, int v)
{
	if(v > ptr->val)
		printf("ERROR: Value must be less than or equal to the value of the pointer\n");

	ptr->val = v;
	struct node *par = ptr->parent;
	if(par != NULL && ptr->val < par->val)
	{
		cut(h, ptr, par);
		cascading_cut(h, par);
	}

	if(ptr->val < h->min->val)
		h->min = ptr;

	return h;
}

struct heap* heap_delete(struct heap *h, struct node *x)
{
	h = node_decrease(h, x, INT_MIN);
	extract_min(h);

	return h;
}

int main()
{
	int option;

	struct heap *h = heap_create();
	struct node *n, *saved = NULL;

	for(int i = 1; i < 16; i++)
	{
		n = (struct node*)malloc(sizeof(struct node));
		n->val = i*10;
		if(n->val == 80)
			saved = n;
		h = heap_insert(h, n);
	}

	while(1)
	{
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Display\n");
		printf("4.Min\n");
		printf("5.Extract Min\n");
		printf("6.Decrease\n");
		printf("7.Quit\n");
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
				h = heap_delete(h, saved);
				printf("Deleted!\n");
				break;
			case 3:
				printf("Tree is :\n");
				heap_display(h);
				break;
			case 4:
				heap_min(h);
				break;
			case 5:
				if(h->min != NULL)
					extract_min(h);
				else
					printf("Heap is empty!\n");
				break;
			case 6:
				h = node_decrease(h, saved, 5);
				break;
			case 7:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
