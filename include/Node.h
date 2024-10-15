#pragma once
#include <stdlib.h>
#include "Edge.h"

typedef struct Node
{
    char* name;
    struct Edge* firstEdge;
} Node;

Node* nodeCreate(char* name);
void nodeFree(Node* node);
void nodePrint(Node* node);