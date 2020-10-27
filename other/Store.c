#include <stdio.h>
#include <stdlib.h>

int main()
{
	typedef struct employee
	{
		int emp_code;
		char name[20];
	} employee;

	FILE *fp;
	fp = fopen("employee.txt", "wb");
	if(fp == NULL)
	{
		printf("\n Error opening file!");
		exit(1);
	}

	struct employee e[2];
	printf("\n Enter the details employees");
	for(int i = 0; i < 2; i++)
	{
		printf("\n\n Enter the employee code: ");
		scanf("%d", &e[i].emp_code);
		printf("\n\n Enter the name of the employee: ");
		scanf("%s", e[i].name);
		fwrite(&e[i], sizeof(e[i]), 1, fp);
	}
	
	fclose(fp);
	
	return 0;
}
