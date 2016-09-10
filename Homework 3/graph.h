
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

// A structure to represent an adjacency list node
typedef struct node
{
    int v;
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
 
typedef struct queue
{
    int value;
    struct queue* next;
}Queue;

Node* newListNode(int v);
Graph* createGraph(int size);
void addEdge(Graph* graph, int src, int dest);
void BFS(Graph* g);
void freeGraph(Graph* g);

#endif /* GRAPH_H */

