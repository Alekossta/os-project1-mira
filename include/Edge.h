#pragma once
#include "Transaction.h"
#include "Node.h"

// will be used as a node in our linked list and will store the transaction data
typedef struct Edge
{
    Transaction transaction;
    struct Node* destinationNode;
    struct Edge* next;
} Edge;