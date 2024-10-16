#include "NodeAccount.h"
#include "string.h"

NodeAccount* nodeCreate(char* name)
{
    NodeAccount* newNode = malloc(sizeof(NodeAccount));

    newNode->name = malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    
    newNode->firstEdge = NULL;

    return newNode;
}

void nodeFree(NodeAccount* node)
{
    free(node->name);
}

void nodePrint(NodeAccount* node)
{
    printf("%s\n", node->name);
}