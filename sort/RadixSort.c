#include <stdio.h>

#define size 10

int largest(int arr[], int n)
{
	int large = arr[0];

	for(int i = 1; i < n; i++)
	{
		if(arr[i] > large)
			large = arr[i];
	}

	return large;
} 

void radix_sort(int arr[], int n)
{
	int bucket[size][size], bucket_count[size];
	int remainder, NOP = 0, divisor = 1, large;

	large = largest(arr, n);

	while(large > 0)
	{
		NOP++;
		large /= size;
	}

	for(int pass = 0 ; pass < NOP; pass++) // Initialize the buckets
	{
		for(int i = 0; i < size; i++)
			bucket_count[i] = 0;

		for(int i = 0; i < n; i++)
		{
			// sort the numbers according to the digit at passth place
			remainder = (arr[i] / divisor) % size;
			bucket[remainder][bucket_count[remainder]] = arr[i];
			bucket_count[remainder] += 1;
		}

		// collect the numbers after PASS pass
		int i = 0;
		for(int k = 0; k < size; k++)
		{
			for(int j = 0; j < bucket_count[k]; j++)
			{
				arr[i] = bucket[k][j];
				i++;
			}
		
		}
		
		divisor *= size;
	}
}

int main()
{
	int n = 9;
	int arr[] = { 345, 654, 924, 123, 567, 472, 555, 808, 911 };

	radix_sort(arr, n);

	printf("\n The sorted array is: \n");

	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);
}
