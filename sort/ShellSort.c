#include <stdio.h>

int main()
{
	int n = 10;
	int arr[] = { 5, 2, 3, 7, 6, 8, 1, 9, 4, 0 };

	int flag = 1, gap_size, temp;

	gap_size = n;
	while(flag == 1 || gap_size > 1)
	{
		flag = 1;
		gap_size = (gap_size + 1) / 2;
		for(int i = 0; i < (n - gap_size); i++)
		{
			if(arr[i+gap_size] < arr[i])
			{
				temp = arr[i+gap_size];
				arr[i+gap_size] = arr[i];
				arr[i] = temp;
				flag = 0;
			}
		}
	}

	printf("\n The sorted array is: \n");
	for(int i = 0; i < n; i++)
		printf(" %d\t", arr[i]);
}
