#include <stdio.h>

#define size 100

void merge(int arr[], int beg, int mid, int end)
{
	int i = beg, j = mid+1, index = beg, temp[size];

	for (int i = 0; i < size; i++)
		temp[i] = -1;

	while((i <= mid) && (j <= end))
	{
		if(arr[i] < arr[j])
		{
			temp[index] = arr[i];
			i++;
		}
		else
		{
			temp[index] = arr[j];
			j++;
		}

		index++;
	}

	if(i > mid)
	{
		while(j <= end)
		{
			temp[index] = arr[j];
			j++;
			index++;
		}
	}
	else
	{
		while(i <= mid)
		{
			temp[index] = arr[i];
			i++;
			index++;
		}
	}

	for(int k = beg; k < index; k++)
		arr[k] = temp[k];
}

void merge_sort(int arr[], int beg, int end)
{
	int mid;
	if(beg < end)
	{
		mid = (beg + end) / 2;
		merge_sort(arr, beg, mid);
		merge_sort(arr, mid+1, end);
		merge(arr, beg, mid, end);
	}
}

int main()
{
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	merge_sort(arr, 0, n-1);

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);
}
