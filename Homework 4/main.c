
/* 
 * File:   main.c
 * Author: Holt Skinner
 *          Homework 4
 *          3-24-16
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Graph* read_file(char* filename);
void quit(enum error e, Graph* g);

int main(int argc, char** argv) {

    if(argc != 2)//Incorrect Command line arguments
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    Graph* g = read_file(argv[1]);//Parse file and create graph
    
    Dijkstra(g);//Run Dijkstra's algorithm and print result
    freeGraph(g);
    
    return (EXIT_SUCCESS);
}

Graph* read_file(char* filename)//Read file and create graph
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
    
    int size = 0, source = 0, dest = 0, weight=0;//Placeholders for size and two values read in
    
    if(fscanf(fp,"%d\n", &size) != 1)//Read in size from file
    {
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    
    if(size<=0 || size>UINT_MAX)//Check for invalid numbers
    {
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    
    Graph* g = createGraph(size+1);//I wonder what this does...

    while(!feof(fp))
    {
        if(fscanf(fp, "(%d,%d,%d)\n", &source, &dest, &weight) != 3)//Check for weird inputs
        {
            quit(PARSING_ERROR_INVALID_FORMAT, g);//free memory and exit
        }
        
        else if (source > 0 && source <= size && dest > 0 && dest <= size && weight > 0)//Check if read in value is a possible number 
        {
            addEdge(g, source, dest, weight);//Add edge to graph
        }
        
        else if(source <= 0 || source > size || dest <= 0 || dest > size)//Check for integers not within the range
        {
            quit(INTEGER_IS_NOT_A_VERTEX, g);
        }
        
        else if (isspace(source) || isspace(dest) || isspace(weight))
        {
            continue;//Do nothing and go to next line
        }
        
        else//Everything else
        {
            quit(PARSING_ERROR_INVALID_FORMAT, g);
        }        
    }

    if (fclose(fp) == EOF)//File doesn't close
    {
        quit(FILE_FAILED_TO_CLOSE, g);
    }
    
    return g;
}

void quit(enum error e, Graph* g) 
{
    freeGraph(g);
	exit(e);
}

