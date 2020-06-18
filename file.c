#include <stdio.h>

int main(int argc, char *argv[])	
{		 
	FILE *result = fopen("result.txt", "w");
  	for(int i = 1; i < argc; i++)
	{
		FILE *task_file = fopen(argv[i], "r");
		char c = fgetc(task_file);
		while(c != EOF)
		{	
			printf("%c", c);
			fputc(c, result);
			c = fgetc(task_file);
		}
		printf("\n");
		fputc('\n', result);
		fclose(task_file);
	}

	fclose(result);

	return 0;
}
