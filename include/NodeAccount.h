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
} NodeAccount;

// memory management
NodeAccount* nodeAccountCreate(char* name);
void nodeAccountFree(NodeAccount* node);

// print
void nodeAccountPrint(NodeAccount* node);

// add edges
void nodeAccountAddOutEdge(NodeAccount* node, struct EdgeTransaction* newOutEdge);
void nodeAccountAddInEdge(NodeAccount* node, struct EdgeTransaction* newOutEdge);

// remove edges
void nodeAccountRemoveAllOutEdges(NodeAccount* node);
void nodeAccountRemoveAllInEdges(NodeAccount* node);
void nodeAccountRemoveOutEdge(NodeAccount* node, EdgeTransaction* edgeTransaction);
void nodeAccountRemoveInEdge(NodeAccount* node, EdgeTransaction* edgeTransaction);

// getters
char* nodeGetName(NodeAccount* node);