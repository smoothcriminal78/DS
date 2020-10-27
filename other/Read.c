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
	struct employee e;


	fp = fopen("employee.txt", "rb");
	if(fp == NULL)
	{
		printf("\n Error opening file");
		exit(1);
	}

	printf("\n THE DETAILS OF THE EMPLOYEES ARE ");
	while(1)
	{
		fread(&e, sizeof(e), 1, fp);

		if(feof(fp))
			break;

		printf("\n\n Employee Code: %d", e.emp_code);
		printf("\n\n Name: %s", e.name);
	}

	fclose(fp);

	return 0;
}
