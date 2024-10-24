#include "NodeAccount.h"
#include "string.h"
#include "BytesCounter.h"

NodeAccount* nodeAccountCreate(char* name)
{
    NodeAccount* newNode = malloc(sizeof(NodeAccount));
    bytesCounter += sizeof(NodeAccount);

    newNode->name = malloc(strlen(name) + 1);
    bytesCounter += sizeof(strlen(name) + 1);
    strcpy(newNode->name, name);
    
    newNode->firstOutEdge = NULL;

    return newNode;
}

void nodeAccountFree(NodeAccount* node)
{
    free(node->name);
    free(node);
}

void nodeAccountPrint(NodeAccount* node)
{
    printf("###%s\n", node->name);

    nodeAccountPrintInEdges(node);
    nodeAccountPrintOutEdges(node);
}

void nodeAccountPrintInEdges(NodeAccount* node)
{
    printf("##%s ingoing transactions\n", node->name);
    EdgeTransaction* headIn = node->firstInEdge;
    while (headIn != NULL)
    {
        edgeTransactionPrint(headIn);
        headIn = headIn->nextIn;
    }
}
void nodeAccountPrintOutEdges(NodeAccount* node)
{
    printf("##%s outgoing transactions\n", node->name);
    EdgeTransaction* headOut = node->firstOutEdge;
    while (headOut != NULL)
    {
        edgeTransactionPrint(headOut);
        headOut = headOut->nextOut;
    }
}

void nodeAccountAddOutEdge(NodeAccount* node, EdgeTransaction* newOutEdge)
{
    if(node->firstOutEdge == NULL)
    {
        node->firstOutEdge = newOutEdge;
    }
    else
    {
        EdgeTransaction* head = node->firstOutEdge;
        while(head->nextOut != NULL)
        {
            head = head->nextOut;
        }

        head->nextOut = newOutEdge;
    }
}

void nodeAccountAddInEdge(NodeAccount* node, EdgeTransaction* newInEdge)
{
    if(node->firstInEdge == NULL)
    {
        node->firstInEdge = newInEdge;
    }
    else
    {
        EdgeTransaction* head = node->firstInEdge;
        while(head->nextIn != NULL)
        {
            head = head->nextIn;
        }

        head->nextIn = newInEdge;
    }
}

void nodeAccountRemoveAllOutEdges(NodeAccount* node)
{
    EdgeTransaction* head = node->firstOutEdge;
    while(head != NULL)
    {
        EdgeTransaction* temp = head;
        head = head->nextOut;
        temp->owner = NULL;
        if(temp->destination != NULL)
        {
            nodeAccountRemoveInEdge(temp->destination, temp);
        }
    }
}

void nodeAccountRemoveAllInEdges(NodeAccount* node)
{
    EdgeTransaction* head = node->firstInEdge;
    while(head != NULL)
    {
        EdgeTransaction* temp = head;
        head = head->nextIn;
        temp->destination = NULL;
        if(temp->owner != NULL)
        {
            nodeAccountRemoveOutEdge(temp->owner, temp);
        }
    }
}

void nodeAccountRemoveEdgeWithOtherNode(NodeAccount* node1, NodeAccount* node2)
{

    // we will search in node1 edges in/out
    // then just remove it also from node2


    // in edges
    EdgeTransaction* head = node1->firstInEdge;
    EdgeTransaction* previous = NULL;
    while(head != NULL)
    {
        if(strcmp(head->destination->name, node2->name) == 0)
        {
            // free will happen in node2
            if(previous == NULL)
            {
                if(head->nextIn != NULL)
                {
                    node1->firstInEdge = head->nextIn;
                }
                else
                {
                    node1->firstInEdge = NULL;
                }
                
                head->destination = NULL;
                if(head->owner != NULL)
                {
                    nodeAccountRemoveOutEdge(node2, head);
                }
            }
            else
            {
                previous->nextIn = head->nextIn;
                head->destination = NULL;
                if(head->owner != NULL)
                {
                    nodeAccountRemoveOutEdge(node2, head);
                }
            }

            return;
        }

        previous = head;
        head = head->nextIn;
    }

    // out edges
    head = node1->firstOutEdge;
    previous = NULL;
    while(head != NULL)
    {
        if(strcmp(head->destination->name, node2->name) == 0)
        {
            // free will happen in node2
            if(previous == NULL)
            {
                if(head->nextOut != NULL)
                {
                    node1->firstOutEdge = head->nextOut;
                }
                else
                {
                    node1->firstOutEdge = NULL;
                }

                head->owner = NULL;
                if(head->destination != NULL)
                {
                    nodeAccountRemoveInEdge(node2, head);
                }
            }
            else
            {
                previous->nextOut = head->nextOut;
                head->owner = NULL;
                if(head->destination != NULL)
                {
                    nodeAccountRemoveInEdge(node2, head);
                }
            }

            return;
        }

        previous = head;
        head = head->nextOut;
    }
}

void nodeAccountRemoveOutEdge(NodeAccount* node, EdgeTransaction* edgeTransaction)
{
    EdgeTransaction* head = node->firstOutEdge;
    EdgeTransaction* previous = NULL;
    while(head != NULL)
    {
        if(head == edgeTransaction)
        {
            if(previous == NULL)
            {
                if(head->nextOut != NULL)
                {
                    node->firstOutEdge = head->nextOut;
                }
                else
                {
                    node->firstOutEdge = NULL;
                }
                head->owner = NULL;
                if(head->destination != NULL)
                {
                    nodeAccountRemoveInEdge(head->destination, head);
                }
                else
                {
                    edgeTransactionFree(head);
                }

            }
            else
            {
                previous->nextOut = head->nextOut;
                head->owner = NULL;
                if(head->destination != NULL)
                {
                    nodeAccountRemoveInEdge(head->destination, head);
                }
                else
                {
                    edgeTransactionFree(head);
                }

            }

            return;
        }

        previous = head;
        head = head->nextOut;
    }
}

void nodeAccountRemoveInEdge(NodeAccount* node, EdgeTransaction* edgeTransaction)
{
    EdgeTransaction* head = node->firstInEdge;
    EdgeTransaction* previous = NULL;
    while(head != NULL)
    {
        if(head == edgeTransaction)
        {
            if(previous == NULL)
            {
                if(head->nextIn != NULL)
                {
                    node->firstInEdge = head->nextIn;
                }
                else
                {
                    node->firstInEdge = NULL;
                }
                head->destination = NULL;
                if(head->owner != NULL)
                {
                    nodeAccountRemoveOutEdge(head->owner, head);
                }
                else
                {
                    edgeTransactionFree(head);
                }
            }
            else
            {
                previous->nextIn = head->nextIn;
                head->destination = NULL;
                if(head->owner != NULL)
                {
                    nodeAccountRemoveOutEdge(head->owner, head);
                }
                else
                {
                    edgeTransactionFree(head);
                }
            }

            return;
        }

        previous = head;
        head = head->nextIn;
    }
}

void nodeAccountFindAndModifyEdgeWithNode(NodeAccount* fromNode, NodeAccount* toNode, int oldSum,
int newSum, char* oldDate, char* newDate)
{
    EdgeTransaction* head = fromNode->firstOutEdge;
    while(head != NULL)
    {
        if(head->destination == toNode && head->amount == oldSum && strcmp(head->date, oldDate) == 0)
        {
            head->amount = newSum;
            free(head->date);
            head->date = strdup(newDate);
        }
        head = head->nextOut;
    }
}

char* nodeGetName(NodeAccount* node)
{
    if(node)
    {
        return node->name;
    }
    
    return NULL;
}