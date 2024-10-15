#include "Node.h"
#include "string.h"

Node* nodeCreate(char* name)
{
    Node* newNode = malloc(sizeof(Node));

    newNode->name = malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    
    newNode->firstEdge = NULL;

    return newNode;
}

void nodeFree(Node* node)
{
    free(node->name);
}

void nodePrint(Node* node)
{
    printf("%s\n", node->name);
}