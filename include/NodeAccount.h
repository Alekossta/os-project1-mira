#pragma once
#include <stdlib.h>
#include "EdgeTransaction.h"

typedef struct NodeAccount
{
    char* name;
    struct EdgeTrasnaction* firstOutEdge;
    struct EdgeTransaction* firstInEdge;
    // used in the graph for hashing and seperate chaining
    struct NodeAccount* nextNode;

    // used for DFS
    int visited;
    int stack;
} NodeAccount;

// memory management

NodeAccount* nodeAccountCreate(char* name);
void nodeAccountFree(NodeAccount* node);

// prints

void nodeAccountPrint(NodeAccount* node);
void nodeAccountPrintInEdges(NodeAccount* node);
void nodeAccountPrintOutEdges(NodeAccount* node);

// add edges

void nodeAccountAddOutEdge(NodeAccount* node, struct EdgeTransaction* newOutEdge);
void nodeAccountAddInEdge(NodeAccount* node, struct EdgeTransaction* newOutEdge);

// remove edges

void nodeAccountRemoveAllOutEdges(NodeAccount* node);
void nodeAccountRemoveAllInEdges(NodeAccount* node);

void nodeAccountRemoveEdgeWithOtherNode(NodeAccount* node1, NodeAccount* node2);

void nodeAccountRemoveOutEdge(NodeAccount* node, struct EdgeTransaction* edgeTransaction);
void nodeAccountRemoveInEdge(NodeAccount* nsode, struct EdgeTransaction* edgeTransaction);

// modify edges

void nodeAccountFindAndModifyEdgeWithNode(NodeAccount* fromNode, NodeAccount* toNode, int oldSum,
int newSum, char* oldDate, char* newDate);

// getters

char* nodeGetName(NodeAccount* node);