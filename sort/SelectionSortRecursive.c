#include <stdio.h>
#include <stdlib.h>

int smallest(int arr[], int k, int n)
{
	int pos = k, small = arr[k];

	for(int i = k+1; i < n; i++)
	{
		if(arr[i] < small)
		{
			small = arr[i];
			pos = i;
		}
	}

	return pos;
}

void selection_sort(int arr[], int i, int n)
{
	int pos = smallest(arr, i, n);
	int temp = arr[i];
	arr[i] = arr[pos];
	arr[pos] = temp;

	if(++i < n-1)
		selection_sort(arr, i, n);
}

int main(int argc, char *argv[]) {
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	selection_sort(arr, 0, n);

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);

	return 0;
}
