#pragma once
#include "NodeAccount.h"
#include "stdio.h"

// struct for representing the graph
// nodeMax = max nodes in the graph
// nodeArray = the actual array of pointers to nodes
typedef struct Graph
{
    unsigned nodeMax;
    NodeAccount** nodeArray;
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

// removes a node/account from our graph
int graphRemoveNode(Graph* graph, char* nodeToRemove);

// writes contents of graph to file
void graphWriteToFile(Graph* graph, FILE* file);

//free
void graphFree(Graph* graph); 

// structure for PathNode for a linked list representing a Path
typedef struct PathNode
{
    NodeAccount* nodeAccount;
    struct PathNode* next;
} PathNode;

// adds a new PathNode
void pathAdd(PathNode** head, NodeAccount* nodeAccount);

// Function to pop a node from the beginning of the path
void pathPop(PathNode** head);

// Function to print the path
void pathPrintReverse(PathNode* head);

// Function to free the entire path list
void freePath(PathNode* head);

// Finds circle of a node. Can add restriction of minimum amount of transaction/edge.s
void graphFindCircle(Graph* graph, NodeAccount* nodeToFind, int minAmount);

// Finds path between nodes (starts from nodeFrom and ends at nodeTo)
void graphFindPath(Graph* graph, NodeAccount* nodeFrom, NodeAccount* nodeTo);

// Finds "flows" of transaction starting from a node with a certain length
void graphFindTraceflow(Graph* graph, NodeAccount* nodeStart, int length);