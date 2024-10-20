#include "CommandHandler.h"
#include "NodeAccount.h"
#include "Graph.h"
#include <string.h>

void handleCommand(Graph* graph, Command* command)
{
    if(command->command == 'i')
    {
        for(unsigned i = 0; i < command->param_count; i++)
        {
            NodeAccount* createdNode = nodeAccountCreate(command->params[i]);
            graphAddNode(graph, createdNode);
        }
    }
    else if(command->command == 'n')
    {
        char* nodeFromName = command->params[0];
        char* nodeToName = command->params[1];

        // second param of strtod() returns the character we stopped converting at. we dont really care so NULL
        double amount = strtod(command->params[2], NULL);

        char* date  = command->params[3];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        if(!nodeFrom)
        {
            nodeFrom = nodeAccountCreate(strdup(nodeFromName));
            graphAddNode(graph, nodeFrom);
        }

        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);
        if(!nodeTo)
        {
            nodeTo = nodeAccountCreate(strdup(nodeToName));
            graphAddNode(graph, nodeTo);
        }

        EdgeTransaction* newEdge = edgeTransactionCreate(amount, date, nodeFrom, nodeTo);

        nodeAccountAddOutEdge(nodeFrom, newEdge);
        nodeAccountAddInEdge(nodeTo, newEdge);
    }
    else if(command->command == 'd')
    {
        for(unsigned i = 0; i < command->param_count; i++)
        {
            printf("deleting command: %s", command->params[i]);
            graphRemoveNode(graph, command->params[i]);
        }
    }
    else if(command->command == 'p')
    {
        graphPrint(graph);
    }
}