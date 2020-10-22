#include <stdio.h>

#define MAX 10

void RestoreHeapUp(int *Heap, int index)
{
	int val = Heap[index];
	
	while((index > 1) && (Heap[index/2] < val)) // Check parent's value
	{
		Heap[index] = Heap[index/2];
		index /= 2;
	}
	
	Heap[index] = val;
}
	
void RestoreHeapDown(int *Heap, int index, int n)
{
	int val = Heap[index];
	int j = index * 2;
	
	while(j <= n)
	{
		if((j < n) && (Heap[j] < Heap[j+1])) // Check sibling's value
			j++;
	
		if(Heap[j] < Heap[j/2]) // Check parent's value
			break;
	
		Heap[j/2] = Heap[j];
		j *= 2;
	}
	
	Heap[j/2] = val;
}

int main()
{
	int n = 9;
	int Heap[MAX] = { 0, 5, 2, 3, 7, 6, 8, 1, 9, 4, };

	for(int i = 1; i <= n; i++)
		RestoreHeapUp(Heap, i); // Heapify

	// Delete the root element and heapify the heap
	int j = n;
	for(int i = 1; i <= j; i++)
	{
		int temp = Heap[1];
		Heap[1] = Heap[n];
		Heap[n] = temp;
		n = n-1; // The element Heap[n] is supposed to be deleted
		
		RestoreHeapDown(Heap, 1, n); // Heapify
	}
	n = j;
	
	printf("\n The sorted elements are: ");
	for(int i = 1; i <= n; i++)
		printf(" %d", Heap[i]);
	
	return 0;
}
	
