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

void selection_sort(int arr[], int n)
{
	int pos, temp;

	for(int k = 0; k < n; k++)
	{
		pos = smallest(arr, k, n);
		temp = arr[k];
		arr[k] = arr[pos];
		arr[pos] = temp;
	}
}

int main(int argc, char *argv[]) {
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	selection_sort(arr, n);

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);

	return 0;
}
