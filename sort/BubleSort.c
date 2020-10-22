#include <stdio.h>

void bubble_sort(int *arr, int n)
{
	int temp, flag = 0;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				flag = 1;
				temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}

		if(flag == 0) // array is sorted
			return;
	}
}

int main()
{
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	bubble_sort(arr, n);

	printf("\n The array sorted in ascending order is :\n");
	for(int i = 0; i < n; i++)
		printf("%d\t", arr[i]);

	return 0;
}
