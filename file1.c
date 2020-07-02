#include <stdio.h>
#include <string.h>
#include <malloc.h>

int count_lines(FILE *task_file);

int main(int argc, char *argv[])	
{		 
  	FILE *result = fopen("result.txt", "w");
	if (result == NULL)
    	{
        	perror ("error file opening");
        	return 1;
    	}

	long *str =  malloc(0 * sizeof(long));
	if(str == NULL)
	{
		perror("Не выделилась память");
		return 1;
	}

	int n = 0;
	int counter = 0;

	for(int i = 1; i < argc; i++)
	{
		FILE *task_file = fopen(argv[i], "r");

		if (task_file == NULL)
        	{
        		perror ("error file opening");
        		return 1;
        	}

		char c;									
		while((c = fgetc(task_file)) != EOF)
		{	
			//printf("%c", c);
			fputc(c, result);
		}
		counter += count_lines(task_file);
		str = realloc(str, counter*sizeof(long));
		if(str == NULL) 
		{
			perror("Не хватило выделенной памяти");
			return 1;
		}
		for(int j = n;j < counter; j++)
		{
			fscanf(task_file, "%ld", &str[j]);
			n++;
		}
		for(int i = 0; i < counter - 1; i++)
		{
			for(int j = 0; j < counter - i - 1; j++)
			{
				if(str[j] > str[j+1])
				{
					int temp = str[j];
					str[j] = str[j+1];
					str[j+1] = temp;
				}
			}
		}
		fseek(result, 0, SEEK_SET);
		for(int j = 0;j < counter; j++)
		{
			fprintf(result, "%ld\n", str[j]);
		}
		
		fputc('\n', result);
		fclose(task_file);
	}

	// for(int i = 0 ; i < counter; i++)
	// {
	// 	printf("%ld ", str[i]);
	// }
	printf("Отсортированные файлы лежат в файле result \n");
	fclose(result);
	free(str);
	return 0;
}

int count_lines(FILE *task_file)
{
	int counter = 0;
	fseek(task_file, 0, SEEK_SET);
	while(! feof(task_file))
	{
		fscanf(task_file, "%*[^\n]%*c");
		counter ++;
	}
	fseek(task_file, 0, SEEK_SET);
	return counter;
}
