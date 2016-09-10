#include "graph.h"

//This file contains graph utility functions

// create a new adjacency list node
Node* newListNode(int v)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
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
        g->array[i].head = NULL;
 
    return g;
}
 
// Adds edge to undirected graph
void addEdge(Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of sources The node is added at the beginning
    Node* newNode = newListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
    
    // Since graph is undirected, add an edge from dest to src also
    newNode = newListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    return;
}

void BFS(Graph* g)//prints all distances
{
    //printGraph(g);
    int front =0, back = 1, i;
    int u;//Placeholder
    
    int *distances = malloc(sizeof(int)*(g->size+1));//Array of distances for each node
    int Q[g->size+1];
    
    for(i=0; i<=g->size; i++)//Initialize distances and Q
    {
        Q[i]=-1;
        distances[i] = -1;
    }
    Node* temp;
    Q[0] = 1;//Start at first vertex
    distances[1]=0;//distance from 1 to 1 is 0
    //printf("size=%d\n",g->size);
    while(front < back)
    {
        u = Q[front];//Dequeue first element
        front++;
        printf("u=%d\n",u);
        temp = g->array[u].head;
        
        while(temp != NULL)//For each element in the adjacency list
        {
            printf("     temp->v == %d\n", temp->v);
            if(distances[temp->v] == -1)//If it hasn't been visited yet
            {
                distances[temp->v] = distances[u]+1;//Distance of current node is current depth
                Q[back] = temp->v;//Add current node to Queue
                back++;//Bump "pointer" to end of queue
                
            }
            
            temp = temp->next;//Move to next in adjacency list
        }
        printf("\t back = %d\n", back);
    }
    
    for(i=1; i<=g->size; i++)//Print out
    {
        printf("%d %d\n", i, distances[i]);
    }
   // free(distances);
    //free(Q);
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
    return;
    free(g->array);
}