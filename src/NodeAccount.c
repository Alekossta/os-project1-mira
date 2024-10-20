#include "NodeAccount.h"
#include "string.h"

NodeAccount* nodeAccountCreate(char* name)
{
    NodeAccount* newNode = malloc(sizeof(NodeAccount));

    newNode->name = malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    
    newNode->firstOutEdge = NULL;

    return newNode;
}

void nodeAccountFree(NodeAccount* node)
{
    free(node->name);
}

void nodeAccountPrint(NodeAccount* node)
{
    printf("###%s\n", node->name);


    // print ingoing transactions
    printf("##%s ingoing transactions\n", node->name);
    EdgeTransaction* headIn = node->firstInEdge;
    while (headIn != NULL)
    {
        edgeTransactionPrint(headIn);
        headIn = headIn->next;
    }
    
    // print outgoing transactions
    printf("##%s outgoing transactions\n", node->name);
    EdgeTransaction* headOut = node->firstOutEdge;
    while (headOut != NULL)
    {
        edgeTransactionPrint(headOut);
        headOut = headOut->next;
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
        while(head->next != NULL)
        {
            head = head->next;
        }

        head->next = newOutEdge;
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
        while(head->next != NULL)
        {
            head = head->next;
        }

        head->next = newInEdge;
    }
}

void nodeAccountRemoveAllOutEdges(NodeAccount* node)
{
    EdgeTransaction* head = node->firstOutEdge;
    while(head != NULL)
    {
        nodeAccountRemoveInEdge(head->destination, head);
        EdgeTransaction* temp = head;
        edgeTransactionFree(temp);
    }
}

void nodeAccountRemoveAllInEdges(NodeAccount* node)
{

}

void nodeAccountRemoveOutEdge(NodeAccount* node, EdgeTransaction* edgeTransaction)
{
    EdgeTransaction* head = node->firstOutEdge;
    EdgeTransaction* previous = NULL;
    while(head != NULL)
    {
        if(head == node)
        {
            if(previous == NULL)
            {
                head->owner = NULL;
                if(head->destination != NULL)
                {
                    nodeAccountRemoveInEdge(head->destination, head);
                }
                else
                {
                    edgeTransactionFree(head);
                }
                node->firstOutEdge = NULL;
            }
            else
            {
                previous->next = head->next;
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
    }
}

void nodeAccountRemoveInEdge(NodeAccount* node, EdgeTransaction* edgeTransaction)
{
    EdgeTransaction* head = node->firstInEdge;
    EdgeTransaction* previous = NULL;
    while(head != NULL)
    {
        if(head == node)
        {
            if(previous == NULL)
            {
                head->destination = NULL;
                if(head->owner != NULL)
                {
                    nodeAccountRemoveOutEdge(head->owner, head);
                }
                else
                {
                    edgeTransactionFree(head);
                }
                node->firstInEdge = NULL;
            }
            else
            {
                previous->next = head->next;
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