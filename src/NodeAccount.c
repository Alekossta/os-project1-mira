#include "NodeAccount.h"
#include "string.h"
#include "BytesCounter.h"

NodeAccount* nodeAccountCreate(char* name)
{
    NodeAccount* newNode = malloc(sizeof(NodeAccount));
    bytesCounter += sizeof(NodeAccount);

    newNode->name = strdup(name);
    bytesCounter += strlen(name) + 1;
    
    newNode->firstOutEdge = NULL;
    newNode->firstInEdge = NULL;
    newNode->nextNode = NULL;

    return newNode;
}

void nodeAccountFree(NodeAccount* node)
{
    bytesCounter -= strlen(node->name) + 1;
    free(node->name);
    bytesCounter -= sizeof(NodeAccount);
    free(node);
}

void nodeAccountPrint(NodeAccount* node)
{
    printf("#%s\n", node->name);

    nodeAccountPrintInEdges(node);
    nodeAccountPrintOutEdges(node);
}

void nodeAccountPrintInEdges(NodeAccount* node)
{
    EdgeTransaction* headIn = node->firstInEdge;
    while (headIn != NULL)
    {
        edgeTransactionPrint(headIn);
        headIn = headIn->nextIn;
    }
}
void nodeAccountPrintOutEdges(NodeAccount* node)
{
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
    EdgeTransaction* head = node1->firstInEdge;
    EdgeTransaction* previous = NULL;
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

int nodeAccountFindAndModifyEdgeWithNode(NodeAccount* fromNode, NodeAccount* toNode, int oldSum,
int newSum, char* oldDate, char* newDate)
{
    EdgeTransaction* head = fromNode->firstOutEdge;
    while(head != NULL)
    {
        if(head->destination == toNode && head->amount == oldSum && strcmp(head->date, oldDate) == 0)
        {
            head->amount = newSum;
            bytesCounter -= (strlen(head->date) + 1);
            free(head->date);
            head->date = strdup(newDate);
            bytesCounter += strlen(newDate) + 1; // strdup uses malloc
            return 1;
        }
        head = head->nextOut;
    }

    return 0;
}