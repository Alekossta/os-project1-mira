#include "NodeAccount.h"
#include "string.h"

NodeAccount* nodeAccountCreate(char* name)
{
    NodeAccount* newNode = malloc(sizeof(NodeAccount));

    newNode->name = malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    
    newNode->firstEdge = NULL;

    return newNode;
}

void nodeAccountFree(NodeAccount* node)
{
    free(node->name);
}

void nodeAccountPrint(NodeAccount* node)
{
    printf("%s\n", node->name);
}