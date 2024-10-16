#pragma once
#include <stdlib.h>
#include "EdgeTransaction.h"

typedef struct NodeAccount
{
    char* name;
    struct EdgeTrasnaction* firstEdge;
    // used in the graph for hashing and seperate chaining
    struct NodeAccount* nextNode; 
} NodeAccount;

NodeAccount* nodeAccountCreate(char* name);
void nodeAccountFree(NodeAccount* node);
void nodeAccountPrint(NodeAccount* node);