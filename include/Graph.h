#pragma once
#include "NodeAccount.h"
#include "stdio.h"

// our graph will be an array of nodes
// each node will have a linked list of edges that indicate its transactions to other accounts
typedef struct Graph
{
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


//free
void graphFree(Graph* graph); 

typedef struct PathNode
{
    NodeAccount* nodeAccount;
    struct PathNode* next;
} PathNode;

void pathAdd(PathNode** head, NodeAccount* nodeAccount);

// Function to pop a node from the beginning of the path
void pathPop(PathNode** head);

// Function to print the path
void pathPrintReverse(PathNode* head);

// Function to free the entire path list
void freePath(PathNode* head);

// Modified cycleUtil function to store path
void cycleUtil(Graph* graph, NodeAccount* currentNode, NodeAccount* startingNode, PathNode** path, int minAmount);

// Function to find and return the path of a cycle in the graph
void graphFindCircle(Graph* graph, NodeAccount* nodeToFind, int minAmount);

void graphFindPath(Graph* graph, NodeAccount* nodeFrom, NodeAccount* nodeTo);