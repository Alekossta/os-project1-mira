#pragma once
#include "NodeAccount.h"
#include "stdio.h"

// our graph will be an array of nodes
// each node will have a linked list of edges that indicate its transactions to other accounts
typedef struct Graph
{
    unsigned nodeNum;
    unsigned nodeMax;
    NodeAccount** nodeArray; // an array of pointers to nodes
} Graph;

// creates the graph (we suppose we will only have one graph)
Graph graphCreate();

// adds an already created node to a graph
void graphAddNode(Graph* graph, NodeAccount* newNode);

// prints the nodes of the graph
void graphPrint(Graph* graph);

// finds a node. O(1). we use hash map
NodeAccount* graphFindNode(Graph* graph, char* nodeName);

// hash function. it receives a key (node name) and returns the index for our hashmap (array)
unsigned graphHash(Graph* graph, char* key);

void graphRemoveNode(Graph* graph, char* nodeToRemove);

// writes contents of graph to file
void graphWriteToFile(Graph* graph, FILE* file);