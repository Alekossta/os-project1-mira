#include "Graph.h"
#include "stdlib.h"

Graph graphCreate()
{
    Graph newGraph;
    newGraph.nodeArray = NULL;
    newGraph.nodeNum = 0;
    return newGraph;
}

void graphAddNode(Graph* graph, Node* newNode)
{
    if(graph->nodeArray == NULL)
    {

        graph->nodeArray = malloc(sizeof(Node*));
        graph->nodeArray[0] = newNode;
        graph->nodeNum++;
    }
    else
    {
        graph->nodeNum++;
        graph->nodeArray = realloc(graph->nodeArray, graph->nodeNum * sizeof(Node*));
        graph->nodeArray[graph->nodeNum - 1] = newNode; 
    }
}

void graphPrint(Graph* graph)
{
    for(unsigned i = 0; i < graph->nodeNum; i++)
    {
        nodePrint(graph->nodeArray[i]);
    }
}