#include <stdio.h>
#include <string.h>
#include <malloc.h>

int count_lines(FILE *task_file);

int main(int argc, char *argv[])	
{
	FILE *result = fopen("result.txt", "w+");
    
    if (result == NULL)
    {
        perror ("error file opening");
        return 1;
    }

	int first = 0;
	
	for(int i = 1; i < argc; i++)
	{
		FILE *task_file = fopen(argv[i], "r");

        if (task_file == NULL)
        {
        	perror ("error file opening");
        	return 1;
        }

		int c = 0;
		while((fscanf(task_file, "%d", &c)) != EOF)
		{	
			fprintf(result, "%d\n", c);
			
			if(first == 0)
			{
				first++;
				continue;
			}
			
			fseek(result, 0, SEEK_SET);
			
			for(int i = 0;i < count_lines(result) - 2; i++)
			{
				for(int j = 0; j < count_lines(result) - i - 2; j++)
				{
					long loc = ftell(result);
                    			if (loc == -1L)
					{
						perror("error");
						return 1;
					}
					int a = 0;
					fscanf(result, "%d", &a);

					long pos = ftell(result);
                    			if (pos == -1L)
					{
						perror("error");
						return 1;
					}
					int b = 0;
					fscanf(result, "%d", &b);

					if(a > b)
					{
						fseek(result, loc, SEEK_SET);
						fprintf(result, "%d\n", b);
						fprintf(result, "%d\n", a);
					}
					fseek(result, pos+1, SEEK_SET);
				}
				fseek(result, 0, SEEK_SET);
			}
			fseek(result, 0, SEEK_END);
		}
		
		fclose(task_file);
	}

	printf("Отсортированные файлы лежат в файле result \n");
	fclose(result);

	return 0;
}

int count_lines(FILE *task_file)
{
	int counter = 0;
	long save = ftell(task_file);
	fseek(task_file, 0, SEEK_SET);
	while(! feof(task_file))
	{
		fscanf(task_file, "%*[^\n]%*c");
		counter ++;
	}
	fseek(task_file, save, SEEK_SET);
	return counter;
}
