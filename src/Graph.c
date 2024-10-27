#include "Graph.h"
#include "stdlib.h"
#include "string.h"
#include "BytesCounter.h"

Graph graphCreate(unsigned nodeMax)
{
    Graph newGraph;
    newGraph.nodeArray = malloc(sizeof(NodeAccount*) * nodeMax);
    bytesCounter += sizeof(NodeAccount*) * nodeMax;
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
                nodeAccountPrint(head);
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

int graphRemoveNode(Graph* graph, char* nodeToRemove)
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
            return 1;
        }

        previousNode = currentNode;
        currentNode = currentNode->nextNode;
    }

    return 0; // did not find node
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

void pathAdd(PathNode** head, NodeAccount* nodeAccount) {
    PathNode* newPathNode = (PathNode*)malloc(sizeof(PathNode));
    newPathNode->nodeAccount = nodeAccount;
    newPathNode->next = *head;
    *head = newPathNode;
}

void pathPop(PathNode** head) {
    if (*head != NULL) {
        PathNode* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void pathPrintReverse(PathNode* head) {
    int count = 0;
    PathNode* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    NodeAccount** nodes = (NodeAccount**)malloc(sizeof(NodeAccount*) * count);
    temp = head;
    for (int i = count - 1; i >= 0; i--) {
        nodes[i] = temp->nodeAccount;
        temp = temp->next;
    }

    for (int i = 0; i < count; i++) {
        printf("%s ", nodes[i]->name);
        if (i < count - 1) {
            printf(", ");
        }
    }

    free(nodes);
}

void freePath(PathNode* head) {
    while (head != NULL) {
        PathNode* temp = head;
        head = head->next;
        free(temp);
    }
}

void cycleUtil(Graph* graph, NodeAccount* currentNode, NodeAccount* startingNode, PathNode** path, int minAmount) {
    currentNode->visited = 1;
    pathAdd(path, currentNode);

    EdgeTransaction* edge = currentNode->firstOutEdge;
    while (edge != NULL) {
        if(edge->amount >= minAmount)
        {
            NodeAccount* neighbor = edge->destination;
            if (neighbor == startingNode) {
                printf("Cycle: ");
                pathPrintReverse(*path);
                printf(", %s\n", startingNode->name);
            } else if (!neighbor->visited) {
                cycleUtil(graph, neighbor, startingNode, path, minAmount);
            }
        }

        edge = edge->nextOut;
    }

    currentNode->visited = 0;
    pathPop(path);
}

void graphFindCircle(Graph* graph, NodeAccount* nodeToFind, int minAmount) {
    for (unsigned i = 0; i < graph->nodeMax; i++) {
        NodeAccount* node = graph->nodeArray[i];
        while (node != NULL) {
            node->visited = 0;
            node = node->nextNode;
        }
    }

    PathNode* path = NULL;
    cycleUtil(graph, nodeToFind, nodeToFind, &path, minAmount);
    freePath(path);
}

// here visited means is in path to avoid looking in the path linked list
int graphFindPathUtil(Graph* graph, NodeAccount* startingNode, NodeAccount* goalNode, PathNode** path)
{
    startingNode->visited = 1;
    pathAdd(path, startingNode);

    if(startingNode == goalNode)
    {
        pathPrintReverse(*path);
        return 1;
    }

    EdgeTransaction* head = startingNode->firstOutEdge;
    while(head)
    {
        NodeAccount* neighbor = head->destination;
        if(neighbor->visited == 0)
        {
            if(graphFindPathUtil(graph,neighbor, goalNode, path))
                return 1;
        }
        head = head->nextOut;
    }

    startingNode->visited = 0;
    pathPop(path);
    return 0;
}

void graphFindPath(Graph* graph, NodeAccount* nodeFrom, NodeAccount* nodeTo)
{
    for (unsigned i = 0; i < graph->nodeMax; i++) {
        NodeAccount* node = graph->nodeArray[i];
        while (node != NULL) {
            node->visited = 0;
            node = node->nextNode;
        }
    }
    PathNode* path = NULL;
    if(!graphFindPathUtil(graph, nodeFrom, nodeTo, &path))
    {
        printf("did not found path\n");
    }
}

void graphFindTraceflowUtil(Graph* graph, NodeAccount* nodeStart, int length, PathNode** path, int currentLength)
{
    if(currentLength == length + 1)
    {
        pathPrintReverse(*path);
        printf("\n");
        return;
    }

    EdgeTransaction* head = nodeStart->firstOutEdge;
    while(head != NULL)
    {
        pathAdd(path, head->destination);
        graphFindTraceflowUtil(graph, head->destination, length, path, currentLength + 1);
        pathPop(path);
        head = head->nextOut;
    }
}

void graphFindTraceflow(Graph* graph, NodeAccount* nodeStart, int length)
{
    PathNode* path = NULL;
    pathAdd(&path, nodeStart);
    graphFindTraceflowUtil(graph,nodeStart, length, &path, 1);
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
    
    bytesCounter -= (sizeof(NodeAccount*) * (graph->nodeMax));
    free(graph->nodeArray);
}