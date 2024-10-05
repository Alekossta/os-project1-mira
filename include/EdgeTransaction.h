#pragma once
#include "NodeAccount.h"
#include "Date.h"

struct EdgeTransaction
{
    NodeAccount* fromAccount;
    NodeAccount* toAccount;
    double amount;
    Date date;
};