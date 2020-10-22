#include <stdio.h> 
  
int min(int x, int y)
{ 
	return (x <=y ) ? x : y;
} 
  
int fibMonaccianSearch(int arr[], int x, int n) 
{ 
    int fib1 = 0, fib2 = 1;
    int fib = fib1 + fib2;
  
    while(fib < n) 
    { 
        fib1 = fib2; 
        fib2 = fib; 
        fib  = fib1 + fib2; 
    } 
  
    int offset = -1; 
  
    while(fib > 1) 
    { 
        int i = min(offset + fib1, n-1); 
  
        if(arr[i] < x) 
        { 
            fib = fib2; 
            fib2 = fib1; 
            fib1 = fib - fib2; 
            offset = i; 
        } 
        else if(arr[i] > x)
		{ 
            fib = fib1; 
            fib2 = fib2 - fib1; 
            fib1 = fib - fib2; 
        } 
        else 
			return i; 
    } 
  
    if(fib2 && arr[offset+1] == x)
		return offset+1; 
  
    return -1; 
} 
  
int main(void) 
{ 
    int arr[] = {10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    int x = 80; 

    printf("Found at index: %d", 
	fibMonaccianSearch(arr, x, n)); 

    return 0; 
} 
