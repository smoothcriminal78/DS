#include <stdio.h>
#include <stdlib.h>

#define M 97

int arr[M] = {-1};

int division_method(int x)
{
	return x % M;
}

int multiplication_method(int x)
{
	float A = 0.618033;
	return M * (x * A - ((int) (x*A)));
}

int mid_square_method(int x)
{
	int digits[10];

	int k = x * x;
	int n = 0;

	while(k / 10 > 0)
	{
		digits[n++] = k % 10;	
		k /= 10;
	}

	digits[n++] = k % 10;	

	if(n == 1)
		return digits[n-1];
	else
		return digits[n/2] * 10 + digits[(n/2 - 1)];
}

int folding_method(int x)
{
	int digits[10];

	int n = 0;
	while(x / 10 > 0)
	{
		digits[n++] = x % 10;	
		x /= 10;
	}

	digits[n++] = x % 10;	

	int k = 0;
	for(int i = 0; i < n; i++)
	{
		if(i % 2 == 0)		
			k += digits[n-i-1] * 10;
		else
			k += digits[n-i-1];	
	}

	return k;
}

/* Probing */
int linear_probing(int p)
{
	for(int i = p+1; i < M; i++)
	{
		if(arr[i] == -1)			
			return i;
	}

	for(int i = 0; i < p; i++)
	{
		if(arr[i] == -1)			
			return i;
	}


	return -1;
}

int quadratic_probing(int p)
{
	int c1 = 1, c2 = 3;

	for(int i = 0; i < M; i++)
	{
		int h = (p + c1*i + c2*i) % M;

		if(arr[h] == -1)			
			return h;
	}

	return -1;
}

int double_hashing(int val)
{
	printf("VAL: %d\n", val);
	int h1 = (val+1) % 97;
	int h2 = (val+1) % 8;

	for(int i = 0; i < M; i++)
	{
		int h = (h1 + i*h2) % 97; 

		printf("H: %d\n", h);

		if(arr[h] == -1)			
			return h;
	}

	return -1;
}

void display()
{
	printf("\nArray: ");
	for (int i = 0; i < M; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void insert(int val)
{
	int pos = division_method(val);

	if(arr[pos] != -1)
	{
		/* pos = linear_probing(pos); */
		/* pos = quadratic_probing(pos); */
		pos = double_hashing(val);
		if(pos == -1)
		{
			printf("Overflow\n");
			display();
			exit(0);
		}
	}

	printf("Inserting at pos: %d\n", pos);
	arr[pos] = val;
}

int h(int val, int n)
{
	return val % n;
}

int main()
{
	/* for (int i = 0; i < M; i++) */
	/* 	arr[i] = -1; */

	/* for (int i = 0; i < M; i++) */
	/* 	insert(i%2); */
	/* display(); */

	/* Rehashing */
	int rehash_n = 5;
	int *rehash_arr = (int*) malloc(rehash_n * sizeof(int));

	for (int i = 0; i < rehash_n; i++)
		rehash_arr[i] = -1;
	
	for (int i = 0; i <= rehash_n; i++)
	{
		int _h = h(i, rehash_n);
		if(rehash_arr[_h] != -1)
		{
			printf("Rehashing\n");
			rehash_n *= 2;
			rehash_arr = (int*) realloc(rehash_arr, rehash_n * sizeof(int));
			rehash_arr[h(i, rehash_n)] = i;
			break;
		}
		else
			rehash_arr[_h] = i;
	}

	/* Display */
	printf("Rehashing array: ");
	for (int i = 0; i < rehash_n; i++)
		printf("%d ", rehash_arr[i]);
}
