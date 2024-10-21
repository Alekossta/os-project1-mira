#pragma once
#include "NodeAccount.h"

// will be used as a node in our linked list and will store the transaction data
typedef struct EdgeTransaction
{
    struct NodeAccount* owner;
    struct NodeAccount* destination;
    struct EdgeTransaction* nextIn;
    struct EdgeTransaction* nextOut;
    char* date;
    double amount;
} EdgeTransaction;

EdgeTransaction* edgeTransactionCreate(double amount, char* date,struct NodeAccount* owner,
 struct NodeAccount* destination);
void edgeTransactionFree(EdgeTransaction* edgeTransaction);
void edgeTransactionPrint(EdgeTransaction* edgeTransaction);