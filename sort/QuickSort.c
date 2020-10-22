#include <stdio.h>

#define size 100

int partition(int a[], int beg, int end)
{
	int left, right, temp, loc, flag;
	loc = left = beg;
	right = end;
	flag = 0;

	while(flag != 1)
	{
		while((a[loc] <= a[right]) && (loc != right))
			right--;

		if(loc == right)
			flag = 1;
		else if(a[loc] > a[right])
		{
			temp = a[loc];
			a[loc] = a[right];
			a[right] = temp;
			loc = right;
		}

		if(flag != 1)
		{
			while((a[loc] >= a[left]) && (loc != left))
				left++;

			if(loc == left)
				flag = 1;
			else if(a[loc] < a[left])
			{
				temp = a[loc];
				a[loc] = a[left];
				a[left] = temp;
				loc = left;
			}
		}
	}

	return loc;
}

void quick_sort(int a[], int beg, int end)
{
	int loc;

	if(beg < end)
	{
		loc = partition(a, beg, end);
		quick_sort(a, beg, loc-1);
		quick_sort(a, loc+1, end);
	}
}

int main()
{
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	quick_sort(arr, 0, n-1);

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);
}
