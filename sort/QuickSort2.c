#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high)
{
	/* Randomized pivot */
	int r = low + rand() % (high - low);
	int k = arr[r];
	arr[r] = arr[high];
	arr[high] = k;

	int pivot = arr[high];

	int i = low;
	for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
            i++;
        }
    }

	int temp = arr[i];
	arr[i] = arr[high];
	arr[high] = temp;

    return i;
}

void quick_sort(int arr[], int low, int high)
{
	if(low < high)
	{
		int pv = partition(arr, low, high);

		quick_sort(arr, low, pv - 1);
		quick_sort(arr, pv + 1, high);
	}
}

int main()
{
	int n = 10;
	int arr[] = { 4, 2, 3, 7, 6, 8, 1, 9, 0, 5 };
	/* int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }; */

	quick_sort(arr, 0, n-1);

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);
}
