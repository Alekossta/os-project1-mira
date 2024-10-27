#pragma once
#include <stdlib.h>
#include "EdgeTransaction.h"

// struct for storing nodes/accounts information
// name = name of account
// firstOutEdge = head of linked list of outgoing edges
// firstInEdge = head of linked list of ingoing edges
// nextNode = used for seperate chaining in the hash map
// visited = used for search algorithms (DFS)
// stack = used for search algorithms (DFS)
typedef struct NodeAccount
{
    char* name;
    struct EdgeTrasnaction* firstOutEdge;
    struct EdgeTransaction* firstInEdge;
    struct NodeAccount* nextNode;
    int visited;
    int stack;
} NodeAccount;

// create new account
NodeAccount* nodeAccountCreate(char* name);

// free account 
void nodeAccountFree(NodeAccount* node);

// prints infromation of account
void nodeAccountPrint(NodeAccount* node);

// prints all ingoing transactions of account
void nodeAccountPrintInEdges(NodeAccount* node);

// prints all outgoing transactions of account
void nodeAccountPrintOutEdges(NodeAccount* node);

// adds outgoing edge (does not actually create the transaction)
void nodeAccountAddOutEdge(NodeAccount* node, struct EdgeTransaction* newOutEdge);

// adds ingoings edge (does not actually create the transaction)
void nodeAccountAddInEdge(NodeAccount* node, struct EdgeTransaction* newOutEdge);

// removes all outgoing edges of node
void nodeAccountRemoveAllOutEdges(NodeAccount* node);

// removes all ingoing edges of node
void nodeAccountRemoveAllInEdges(NodeAccount* node);

// remove first encountered edge between two nodes
void nodeAccountRemoveEdgeWithOtherNode(NodeAccount* node1, NodeAccount* node2);

// remove outgoing edge. Complexity is O(n)
void nodeAccountRemoveOutEdge(NodeAccount* node, struct EdgeTransaction* edgeTransaction);

// remove ingoing edge. Complexity is O(n)
void nodeAccountRemoveInEdge(NodeAccount* nsode, struct EdgeTransaction* edgeTransaction);

// modify edge. returns 0 if was not found and 1 if was modified.
int nodeAccountFindAndModifyEdgeWithNode(NodeAccount* fromNode, NodeAccount* toNode, int oldSum,
int newSum, char* oldDate, char* newDate);