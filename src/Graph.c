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
    for(unsigned i = 0; i < graph->nodeMax; i++)
    {
        if(graph->nodeArray[i] != NULL)
        {
            NodeAccount* head = graph->nodeArray[i];
            while(head != NULL)
            {
                nodeAccountPrint(graph->nodeArray[i]);
                head = head->nextNode;
            }
        }
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

NodeAccount* graphFindNode(Graph* graph, char* nodeName)
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

    return NULL;
}

void graphRemoveNode(Graph* graph, char* nodeToRemove)
{
    unsigned hashIndex = graphHash(graph, nodeToRemove);
    NodeAccount* currentNode =  graph->nodeArray[hashIndex];
    NodeAccount* previousNode = NULL;

    while (currentNode != NULL)
    {
        if(strcmp(currentNode->name, nodeToRemove) == 0)
        {
            if(previousNode == NULL)
            {
                graph->nodeArray[hashIndex] = currentNode->nextNode;
            }
            else
            {
                previousNode->nextNode = currentNode->nextNode;
            }
            nodeAccountFree(currentNode);
            return;
        }

        previousNode = currentNode;
        currentNode = currentNode->nextNode;
    }
}