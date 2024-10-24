#include "Graph.h"
#include "stdlib.h"
#include "string.h"
#include "BytesCounter.h"

Graph graphCreate(unsigned nodeMax)
{
    Graph newGraph;
    newGraph.nodeArray = malloc(sizeof(NodeAccount*) * nodeMax);
    bytesCounter += sizeof(NodeAccount*) * nodeMax;
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
            nodeAccountRemoveAllInEdges(currentNode);
            nodeAccountRemoveAllOutEdges(currentNode);
            nodeAccountFree(currentNode);
            return;
        }

        previousNode = currentNode;
        currentNode = currentNode->nextNode;
    }
}

void graphWriteToFile(Graph* graph, FILE* file)
{
    for(unsigned i = 0; i < graph->nodeMax; i++)
    {
        if(graph->nodeArray[i] != NULL)
        {
            NodeAccount* headNode = graph->nodeArray[i];
            while(headNode != NULL)
            {
                EdgeTransaction* headEdge = headNode->firstOutEdge;
                while(headEdge != NULL)
                {
                    fprintf(file, "%s %s %d %s\n", headEdge->owner->name, headEdge->destination->name
                    , headEdge->amount, headEdge->date);
                    headEdge = headEdge->nextOut;
                }

                headNode = headNode->nextNode;
            }
        }
    }
}

int cycleUtil(Graph* graph, NodeAccount* node)
{
    EdgeTransaction* head = node->firstOutEdge;
    while(head != NULL)
    {
        NodeAccount* neighbor = head->destination;
        if(neighbor->visited == 0)
        {
            if(cycleUtil(graph,neighbor) == 1)
            {
                return 1;
            }
        }
        else if(neighbor->stack == 1)
        {
            return 1;
        }


        head = head->nextOut;
    }

    node->stack = 0;
    return 0;
}

void graphFindCircle(Graph* graph, NodeAccount* nodeToFind)
{
    // set every node to unvisited from other searches
    for(unsigned i = 0; i < graph->nodeMax; i++)
    {
        if(graph->nodeArray[i] != NULL)
        {

            NodeAccount* head = graph->nodeArray[i];
            while(head != NULL)
            {
                head->visited = 0;
                head->stack = 0;
                head = head->nextNode;
            }
        }
    }

    int cycleResult = cycleUtil(graph,nodeToFind);
    printf("Cycle result: %d", cycleResult);
}

void graphFree(Graph* graph)
{
    for(unsigned i = 0; i < graph->nodeMax; i++)
    {
        if(graph->nodeArray[i] != NULL)
        {
            NodeAccount* headNode = graph->nodeArray[i];
            while(headNode != NULL)
            {
                EdgeTransaction* headEdge = headNode->firstOutEdge;
                while(headEdge != NULL)
                {
                    EdgeTransaction* temp = headEdge->nextOut;
                    edgeTransactionFree(headEdge);
                    headEdge = temp;
                }

                NodeAccount* tempNext = headNode->nextNode;
                nodeAccountFree(headNode);
                headNode = tempNext;
            }
        }
    }

    free(graph->nodeArray);
}