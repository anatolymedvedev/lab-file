#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char *argv[])	
{
	FILE *result = fopen("result.txt", "w+");
    
    if (result == NULL)
    {
        perror ("error file opening");
        return 1;
    }

	FILE *file1 = fopen(argv[1], "r");

    if (file1 == NULL)
    {
        perror ("error file opening");
        return 1;
    }

	FILE *file2 = fopen(argv[2], "r");

    if (file2 == NULL)
    {
        perror ("error file opening");
        return 1;
    }
    
    int c = 0; 
    int q = 0;

    long loc = 0;
    long pos = 0;

    while(((fscanf(file1, "%d", &c)) | (fscanf(file2, "%d", &q))) != EOF)
    {
        if(c < q)
        {
            fprintf(result, "%d\n", c);
            fseek(file2, pos, SEEK_SET);
        } 
        else
        {
            fprintf(result, "%d\n", q);
            fseek(file1, loc, SEEK_SET);
        }
        loc = ftell(file1);
        pos = ftell(file2);
    }
    
    if(c < q)
    {
        fprintf (result, "%d\n", q);
    } 
    else
    {
        fprintf (result, "%d\n", c);
    }

    while((fscanf(file1, "%d", &c)) != EOF)
    {
        fprintf(result, "%d\n", c);
    }  
    
    while((fscanf(file2, "%d", &q)) != EOF)
    {
        fprintf(result, "%d\n", q);
    }

    fclose(file1);
    fclose(file2);
    fclose(result);

    printf("Отсортированные файлы лежат в файле result \n");
    return 0;
}
