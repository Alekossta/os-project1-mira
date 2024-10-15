#pragma once
#include "Node.h"

// our graph will be an array of nodes
// each node will have a linked list of edges that indicate its transactions to other accounts
typedef struct Graph
{
    unsigned nodeNum;
    Node** nodeArray; // an array of pointers to nodes
} Graph;

// creates the graph (we suppose we will only have one graph)
Graph graphCreate();

// adds an already created node to a graph
void graphAddNode(Graph* graph, Node* newNode);

// prints the nodes of the graph
void graphPrint(Graph* graph);