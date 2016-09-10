
/* 
 * File:   main.c
 * Author: Holt Skinner
 *          hastg2
 *          
 */

#include <ctype.h>
#include <limits.h>
#include "input_error.h"
#include "vector.h"

void read_file(char* filename, Vector* v);
void quicksort(int* x, int first, int last);
void search_arrays(int* a1, int* a2, int size1, int size2);

int main(int argc, char** argv) {

    if (argc != 3)//Incorrect commandline arguments
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    Vector v1;
    Vector v2;
    
    init_vector(&v1);
    read_file(argv[1], &v1);//Read in file 1 & load vector1
    
    
    init_vector(&v2);
    read_file(argv[2], &v2);//read in File 2 & load vector 2
    
    quicksort(vector_get_ptr(&v1), 0, vector_size(&v1)-1);//Sort arrays inside vectors
    quicksort(vector_get_ptr(&v2), 0, vector_size(&v2)-1);
    
    search_arrays(vector_get_ptr(&v1), vector_get_ptr(&v2), vector_size(&v1), vector_size(&v2));//Find items in common and print
    
    free_vector(&v1);//Got to prevent memory leaks!
    free_vector(&v2);
    
    return (EXIT_SUCCESS);
}

void read_file(char* filename, Vector* v)
{
    FILE* fp = fopen(filename, "r");
    
    if(!fp)//File doesn't open
    {
        exit(FILE_FAILED_TO_OPEN);
    }
    
    if(feof(fp))//File is empty
    {
        fclose(fp);//Just in case
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    
    int newNum;
    
	while (!feof(fp)) //Parse file data     
        {
            
            if(fscanf(fp, "%d\n", &newNum) != 1)//Checks for weird stuff read in
            {
                exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
            }
            
            else if (newNum >= 0 && newNum < INT_MAX)//Check if read in value is a possible number 
            {
                insert_element_vector(v, newNum);//Insert into vector
            }
            
            else if (isspace(newNum))
            {
                   continue;//Do nothing and go to next line
            }
            
            else
            {
		exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
            }
	}
  
    
    if (fclose(fp) == EOF)//FIle doesn't close
    {
        exit(FILE_FAILED_TO_CLOSE);
    }
    return;
}

void quicksort(int* x, int first, int last)
{
    int pivot, j, temp, i;

     if(first<last)
     {
         pivot=first;
         i=first;
         j=last;

         while(i<j)
         {
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j)
             {
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort(x,first,j-1);
         quicksort(x,j+1,last);
    }
}

void search_arrays(int* a1, int* a2, int size1, int size2)//Finds the intersection of two data sets
{
    int i = 0, j = 0;//Counters
    Vector v;
    init_vector(&v);
    while(i < size1 && j < size2)
    {
        if (a1[i] < a2[j])
        {
            i++;
        }
        else if(a2[j] < a1[i])
        {
            j++;
        }
        else // if the current elements are equal, print out
        {
            printf("%d\n", a1[i]);
            i++;
            j++;
        }
    }
    return;
}