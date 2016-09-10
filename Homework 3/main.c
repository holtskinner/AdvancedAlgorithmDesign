
/* 
 * File:   main.c
 * Author: Holt Skinner
 *          hastg2
 *          3/15/16
 */

#include "graph.h"//Includes stdio & other libs
#include "input_error.h"

Graph* read_file(char* filename);

int main(int argc, char** argv) {

    if(argc != 2)//Incorrect Command line arguments
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    Graph* g = read_file(argv[1]);//Parse file and create graph
    BFS(g);
    freeGraph(g);
   
    return (EXIT_SUCCESS);
}

Graph* read_file(char* filename)
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
    
    int size = 0, source = 0, dest = 0;//Placeholders for size and two values read in
    
    if(fscanf(fp,"%d\n", &size) != 1)//Read in size from file
    {
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    
    if(size<=0 || size>UINT_MAX)//Check for invalid numbers
    {
        exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
    }
    
    Graph* g = createGraph(size);//I wonder what this does...

    while(!feof(fp))
    {
        if(fscanf(fp, "(%d,%d)\n", &source, &dest) != 2)//Check for weird inputs
        {
            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
        }
        else if (source > 0 && source <= size && dest > 0 && dest <= size)//Check if read in value is a possible number 
            {
                addEdge(g, source, dest);//Add edge to graph
            }
        else if(source <= 0 || source > size || dest <= 0 || dest > size)//Check for integers not within the range
        {
            exit(INTEGER_IS_NOT_A_VERTEX);
        }
        else if (isspace(source) || isspace(dest))
            {
                   continue;//Do nothing and go to next line
            }        
        else//Everything else
            {
		exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
            }        
    }


    if (fclose(fp) == EOF)//File doesn't close
    {
        exit(FILE_FAILED_TO_CLOSE);
    }
    
    return g;
}
