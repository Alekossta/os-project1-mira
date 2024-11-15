#include "EdgeTransaction.h"
#include "string.h"
#include "stdio.h"
#include "BytesCounter.h"

EdgeTransaction* edgeTransactionCreate(int amount, char* date,NodeAccount* owner, NodeAccount* destination)
{
    EdgeTransaction* newEdge = malloc(sizeof(EdgeTransaction));
    bytesCounter += sizeof(EdgeTransaction);

    newEdge->destination = destination;
    newEdge->nextIn = NULL;
    newEdge->nextOut = NULL;
    newEdge->amount = amount;
    newEdge->owner = owner;
    newEdge->date = strdup(date);
    bytesCounter += strlen(date) + 1;

    return newEdge;
}

void edgeTransactionFree(EdgeTransaction* edgeTransaction)
{
    bytesCounter -= (strlen(edgeTransaction->date) + 1);
    free(edgeTransaction->date);
    bytesCounter -= sizeof(EdgeTransaction);
    free(edgeTransaction);
}

void edgeTransactionPrint(EdgeTransaction* edgeTransaction)
{
    if(edgeTransaction)
    {
        char* fromName = edgeTransaction->owner->name;
        char* toName = edgeTransaction->destination->name;

        printf("%s %s %d %s\n", fromName, toName,
         edgeTransaction->amount, edgeTransaction->date);    
    }
}