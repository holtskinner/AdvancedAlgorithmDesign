
/* 
 * File:   graph.h
 * Author: Holt
 *
 * Created on March 4, 2016, 3:05 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "input_error.h"

// A structure to represent an adjacency list node
typedef struct node
{
    int v;//Value
    int w;//Weight
    struct node* next;
}Node;
 
//Adjacency list
typedef struct list
{
    Node *head;  // pointer to head node of list
}List;
 
//Graph-Array of adjacency lists
typedef struct graph
{
    int size;//Size
    List* array;
}Graph;

Node* newListNode(int v, int w);//Utility functions
Graph* createGraph(int size);
void addEdge(Graph* graph, int src, int dest, int weight);
void freeGraph(Graph* g);
void Dijkstra(Graph* g);

#endif /* GRAPH_H */

