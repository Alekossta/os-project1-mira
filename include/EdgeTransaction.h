#pragma once
#include "NodeAccount.h"
#include "Date.h"

// will be used as a node in our linked list and will store the transaction data
typedef struct Edge
{
    struct NodeAccount* destinationNode;
    struct Edge* next;
    Date date;
    double amount;
} Edge;