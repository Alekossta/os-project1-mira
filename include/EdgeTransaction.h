#pragma once
#include "NodeAccount.h"

// struct for the edge/transaction
// owner = giving account
// destination = receiving account
// nextIn = next ingoing transaction for our edge. our edges are nodes of a linked list
// nextOut = next outgoing transaction for our edge. our edges are nodes of a linked list
// date = date of transaction
// amount = amount of transaction 
typedef struct EdgeTransaction
{
    struct NodeAccount* owner;
    struct NodeAccount* destination;
    struct EdgeTransaction* nextIn;
    struct EdgeTransaction* nextOut;
    char* date;
    int amount;
} EdgeTransaction;

// Creates a new edge/transaction
EdgeTransaction* edgeTransactionCreate(int amount, char* date,struct NodeAccount* owner,
 struct NodeAccount* destination);

// Frees the edge/transaction
void edgeTransactionFree(EdgeTransaction* edgeTransaction);

// Prints the edge/transaction
void edgeTransactionPrint(EdgeTransaction* edgeTransaction);