#include <stdio.h>
#include <math.h>

#define MAX 20

int jump_search(int a[], int val, int n)
{
	int step = sqrt(n);
	int start = 0, end = step;

	while(end < n && a[end] <= val)
	{
		start = end;
		end += step;

		if(end > n-1)
			end = n;
	}

	for(int i = start; i < end; i++)
	{
		if(a[i] == val)
			return i+1;
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

	int pos = jump_search(arr, val, n);

	if(pos == -1)
		printf("\n %d is not found in the array", val);
	else
		printf("\n %d is found at position %d", val, pos);

	return 0;
}
