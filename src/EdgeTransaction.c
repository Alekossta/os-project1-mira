#include "EdgeTransaction.h"
#include "string.h"

EdgeTransaction* edgeTransactionCreate(double amount, char* date,NodeAccount* owner, NodeAccount* destination)
{
    EdgeTransaction* newEdge = malloc(sizeof(EdgeTransaction));

    newEdge->destination = destination;
    newEdge->next = NULL;
    newEdge->amount = amount;
    newEdge->owner = owner;
    newEdge->date = strdup(date);

    return newEdge;
}

void edgeTransactionFree(EdgeTransaction* edgeTransaction)
{
    free(edgeTransaction->date);

    // to be implemented
}