#include <stdio.h>

void insertion_sort(int arr[], int n)
{
	int j, temp;

	for(int i = 1; i < n; i++)
	{
		temp = arr[i];
		j = i-1;

		while((temp < arr[j]) && (j >= 0))
		{
			arr[j+1] = arr[j];
			j--;
		}

		arr[j+1] = temp;
	}
}

int main()
{
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	insertion_sort(arr, n);

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);

	return 0;
}
