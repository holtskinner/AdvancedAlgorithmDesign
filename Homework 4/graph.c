#include "graph.h"

//This file contains graph utility functions

// create a new adjacency list node
Node* newListNode(int v, int w)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->w = w;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of size vertices
Graph* createGraph(int size)
{
    Graph* g = (Graph*) malloc(sizeof(Graph));
    g->size = size;
 
    // Create an array of adjacency lists.  Size of array will be size
    g->array = (List*)malloc(size * sizeof(List));
 
    // Initialize each list as empty
    int i=0;
    for (i = 0; i <= size; i++)
    {
        g->array[i].head = NULL;
    }
    return g;
}
 
// Adds edge to undirected graph
void addEdge(Graph* graph, int src, int dest, int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    
    Node* newNode = newListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    return;
}

void Dijkstra(Graph* g)
{
    int i=0, front=1, u=-1;
    int size = g->size;
    int* d = malloc(sizeof(int)* size);//current shortest distance
    int* Q = malloc(sizeof(int)* size);//List of unknown shortest paths (Sorry I didn't use a heap) :(
    Node* temp = NULL;
    
    for(i=0; i< g->size; i++)//Initialize all
    {
        d[i] = -1;
        Q[i] = i;//Insert all vertices into Q
    }
    
    d[1] = 0;//Distance from 1 to itself is 0
    Q[1] = 1;
    
    while(front < (g->size))
    {
        u = Q[front];//Extract smallest value
        front++;
        
        if(d[u] == -1)//Go to next loop if parent node hasn't been found yet
        {
            continue;
        }
        temp = g->array[u].head;
        
        while(temp != NULL)//For each element in the adjacency list
        {
            if(d[temp->v] == -1 || d[temp->v] > (d[u] + temp->w))
            {
                d[temp->v] = d[u] + temp->w;
            }
            temp = temp->next;
        }
    }
        
    for(i=1; i<g->size; i++)//Print result
    {
        printf("%d %d\n", i, d[i]);
    }
    return;
}

void freeGraph(Graph* g)
{
    int i=0;
    for(i=0; i<g->size; i++)
    {
        while(g->array[i].head != NULL)
        {
            Node* temp = g->array[i].head;
            g->array[i].head = g->array[i].head->next;
            free(temp);
        }
    }
    free(g->array[i].head);
    //free(g->array);
    return;
}