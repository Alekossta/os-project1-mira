#include "Graph.h"
#include "stdlib.h"
#include "string.h"

Graph graphCreate(unsigned nodeMax)
{
    Graph newGraph;
    newGraph.nodeArray = malloc(sizeof(NodeAccount*) * nodeMax);
    newGraph.nodeNum = 0;
    newGraph.nodeMax = nodeMax;
    return newGraph;
}

void graphAddNode(Graph* graph, NodeAccount* newNode)
{
    unsigned hashIndex = graphHash(graph, newNode->name);

    if(graph->nodeArray[hashIndex] == NULL)
    {
        graph->nodeArray[hashIndex] = newNode;
    }
    else
    {
        NodeAccount* head = graph->nodeArray[hashIndex];
        while(head->nextNode != NULL)
        {
            head = head->nextNode;
        }
        head->nextNode = newNode;
    }
}

void graphPrint(Graph* graph)
{
    for(unsigned i = 0; i < graph->nodeNum; i++)
    {
        nodePrint(graph->nodeArray[i]);
    }
}

unsigned graphHash(Graph* graph, char* key)
{
    unsigned hash = 5381;
    char currentCharacter;

    while((currentCharacter = *key++))
    {
        hash = ((hash << 5) + hash) + currentCharacter;
    }

    return hash % graph->nodeMax;
}

NodeAccount* graphFind(Graph* graph, char* nodeName)
{
    unsigned hashIndex = graphHash(graph,nodeName);

    NodeAccount* head = graph->nodeArray[hashIndex];
    while(head != NULL)
    {
        if(strcmp(head->name, nodeName) == 0)
        {
            return head;
        }

        head = head->nextNode;
    }
}