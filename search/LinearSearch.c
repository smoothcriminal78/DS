#include <stdio.h>
#include <stdlib.h>

#define size 20 // Added so the size of the array can be altered more easily

int main(int argc, char *argv[]) {

	int n = 11;
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21 };

	int num;
	printf("\n Enter the number that has to be searched : ");
	scanf("%d", &num);

	int found = 0, pos = -1;
	for(int i = 0; i < n; i++)
	{
		if(arr[i] == num)
		{
			found =1;
			pos=i;
			printf("\n %d is found in the array at position= %d", num, i+1);
			/* +1 added in line 23 so that it would display the number in
			 * the first place in the array as in position 1 instead of 0 */
			break;
		}
	}

	if(found == 0)
		printf("\n %d does not exist in the array", num);

	return 0;
}
