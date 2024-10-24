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

        int amount = atoi(command->params[2]);
        
        char* date  = command->params[3];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        if(!nodeFrom)
        {
            nodeFrom = nodeAccountCreate(nodeFromName);
            graphAddNode(graph, nodeFrom);
        }

        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);
        if(!nodeTo)
        {
            nodeTo = nodeAccountCreate(nodeToName);
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
            graphRemoveNode(graph, command->params[i]);
        }
    }
    else if(command->command == 'l')
    {
        char* nodeFromName = command->params[0];
        char* nodeToName = command->params[1];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);

        if(nodeFrom && nodeTo)
        {
            nodeAccountRemoveEdgeWithOtherNode(nodeFrom, nodeTo);
        }
        else
        {
            printf("The nodes you provided do not exist\n");
        }
    }
    else if (command->command == 'm')
    {
        char* nodeFromName = command->params[0];
        char* nodeToName = command->params[1];

        int oldSum = atoi(command->params[2]);
        int newSum = atoi(command->params[3]);

        char* oldDate = command->params[4];
        char* newDate = command->params[5];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);

        if(nodeFrom && nodeTo)
        {
            nodeAccountFindAndModifyEdgeWithNode(nodeFrom,nodeTo, oldSum, newSum, oldDate, newDate);
        }        
    }
    else if(command->command == 'f')
    {
        char* nodeNameToLook = command->params[0];
        NodeAccount* nodeToLook = graphFindNode(graph, nodeNameToLook);
        if(nodeToLook)
        {
            nodeAccountPrintOutEdges(nodeToLook);
        }
        else
        {
            printf("This node does not exist\n");
        }
    }
    else if(command->command == 'r')
    {
        char* nodeNameToLook = command->params[0];
        NodeAccount* nodeToLook = graphFindNode(graph, nodeNameToLook);
        if(nodeToLook)
        {
            nodeAccountPrintInEdges(nodeToLook);
        }
        else
        {
            printf("This node does not exist\n");
        }       
    }
    else if(command->command == 'c')
    {
        char* nodeName = command->params[0];
        NodeAccount* nodeToLook = graphFindNode(graph, nodeName);
        if(nodeToLook)
        {
            graphFindCircle(graph, nodeToLook);
        }
        else
        {
            printf("This node does not exist\n");
        }
    }
    else if(command->command == 'p')
    {
        graphPrint(graph);
    }
}