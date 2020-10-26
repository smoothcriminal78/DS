#include <stdio.h>
#include <stdlib.h>

#define sz 10

typedef struct node
{
	int value;
	struct node *next;
} node;

int h(int x)
{
	return x % sz;
}

/* Initializes m location in the chained
 * hash table.
 * The operation takes a running time of
 * O(m) */
void initializeHashTable(node *hash_table[], int m)
{
	for(int i=0; i <= m; i++)
		hash_table[i] = NULL;
}

/* The element is inserted at the beginning of
 * the linked list whose pointer to its head is
 * stored in the location given by h(k).
 * The running time of the insert operation is O(1), as
 * the new key value is always added as the first
 * element of the list irrespective of the size o */
node *insert_value(node *hash_table[], int val)
{
	node *new_node;
	new_node = (node *)malloc(sizeof(node));
	new_node->value = val;
	new_node->next = hash_table[h(val)];
	hash_table[h(val)] = new_node;

	return new_node;
}


/* The element is searched in the linked
 * list whose pointer to its head is stored
 * in the location given by h(k). If search is
 * successful, the function returns a pointer
 * to the node in the linked list; otherwise
 * it returns NULL. The worst case running
 * time of the search operation is given as
 * order of size of the linked list. */
node *search_value(node *hash_table[], int val)
{
	node *ptr;
	ptr = hash_table[h(val)];

	while((ptr != NULL) && (ptr->value != val))
		ptr = ptr->next;

	if((ptr != NULL) && ptr->value == val)
		return ptr;
	else
		return NULL;
}

/* To delete a node from the linked list whose
 * head is stored at the location given by h(k)
 * in the hash table, we need to know the address
 * of the node’s predecessor. We do this using a
 * pointer save. The running time complexity of
 * the delete operation is same as that of the
 * search operation because we need to search the
 * predecessor of the node so that the node can
 * be removed without affecting other nodes in the
 * list. */
void delete_value(node *hash_table[], int val)
{
	node *save, *ptr;
	save = NULL;
	ptr = hash_table[h(val)];

	while ((ptr != NULL) && (ptr->value != val))
	{
		save = ptr;
		ptr = ptr->next;
	}

	if (ptr != NULL)
	{
		save->next = ptr->next;
		free(ptr);
	}
	else
		printf("\nVALUE NOT FOUND\n");
}

void display(node *hash_table[], int ind)
{
	printf("Hash table index: %d:  ", ind);
	node *temp = hash_table[ind];

	while(temp != NULL)
	{
		printf("%d ", temp->value);	
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	node *hash_table[sz];

	initializeHashTable(hash_table, sz);

	for (int i = 0; i < 100; i++)
	{
		insert_value(hash_table, i);
	}

	for (int i = 0; i < 10; i++)
	{
		display(hash_table, i);
	}

	printf("Search: ");
	node *v = search_value(hash_table, 99);
	if(v == NULL)
		printf("Value %d not found!\n", 99);
	else
		printf("Value %d found!\n", v->value);

	printf("Delete:\n");
	delete_value(hash_table, 42);
	for (int i = 0; i < 10; i++)
	{
		display(hash_table, i);
	}
}
