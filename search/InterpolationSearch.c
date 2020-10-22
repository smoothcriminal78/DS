#include <stdio.h>

#define MAX 20

int interpolation_search(int a[], int low, int high, int val)
{
	int mid;

	while(low <= high)
	{
		mid = low + ((high - low) * (val - a[low])) / (a[high] - a[low]);

		if(val == a[mid])
			return mid;

		if(val < a[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

int main()
{
	int n = 11;
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21 };

	int val;
	printf("\n Enter the value to be searched : ");
	scanf("%d", &val);
	int pos = interpolation_search(arr, 0, n-1, val);

	if(pos == -1)
		printf("\n %d is not found in the array", val);
	else
		printf("\n %d is found at position %d", val, pos);

	return 0;
}
