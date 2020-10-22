#include <stdio.h>
#include <stdlib.h>

#define size 10

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
	for(int i = 0; i < n; i++)
	{
		pos = smallest(arr, i, n);
		temp = arr[i];
		arr[i] = arr[pos];
		arr[pos] = temp;
	}
}

int main(int argc, char *argv[])
{
	int n = 11;
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21 };

	selection_sort(arr, n); // Added to sort the array
	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);

	int num;
	printf("\n\n Enter the number that has to be searched: ");
	scanf("%d", &num);

	int beg = 0, end = n-1, mid, found = 0;
	while(beg <= end)
	{
		mid = (beg + end) / 2;
		if(arr[mid] == num)
		{
			printf("\n %d is present in the array at position %d", num, mid+1);
			found = 1;

			break;
		}
		else if(arr[mid] > num)
			end = mid-1;
		else
			beg = mid+1;
	}

	if (beg > end && found == 0)
		printf("\n %d does not exist in the array", num);

	return 0;
}
