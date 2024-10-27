#include "CommandHandler.h"
#include "NodeAccount.h"
#include "Graph.h"
#include <string.h>

void handleCommand(Graph* graph, Command* command)
{
    if(strcmp(command->command, "i") == 0 || strcmp(command->command, "insert") == 0)
    {
        for(unsigned i = 0; i < command->param_count; i++)
        {
            NodeAccount* createdNode = nodeAccountCreate(command->params[i]);
            if(createdNode)
            {
                printf("Succ: %s", command->params[i]);
                graphAddNode(graph, createdNode);
            }
            else
            {
                printf("IssueWith: %s", command->params[i]);
                return;
            }
        }
    }
    else if(strcmp(command->command, "n") == 0 || strcmp(command->command, "insert2") == 0)
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

        if(!nodeFrom)
        {
            printf("Issue with: %s\n", nodeFromName);
            return;
        }

        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);
        if(!nodeTo)
        {
            nodeTo = nodeAccountCreate(nodeToName);
            graphAddNode(graph, nodeTo);
        }

        if(!nodeTo)
        {
            printf("Issue with: %s\n", nodeToName);
            return;
        }

        EdgeTransaction* newEdge = edgeTransactionCreate(amount, date, nodeFrom, nodeTo);

        nodeAccountAddOutEdge(nodeFrom, newEdge);
        nodeAccountAddInEdge(nodeTo, newEdge);
    }
    else if(strcmp(command->command, "d") == 0 || strcmp(command->command, "delete") == 0)
    {
        for(unsigned i = 0; i < command->param_count; i++)
        {
            int result = graphRemoveNode(graph, command->params[i]);
            if(result == 0)
            {
                printf("Non-existing node: %s\n", command->params[i]);
            }
        }
    }
    else if(strcmp(command->command, "l") == 0 || strcmp(command->command, "delete2") == 0)
    {
        char* nodeFromName = command->params[0];
        char* nodeToName = command->params[1];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        if(!nodeFrom)
        {
            printf("Non-existing node: %s", nodeFromName);
            return;
        }
        
        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);
        if(!nodeTo)
        {
            printf("Non-existing node: %s", nodeToName);
            return;
        }

        if(nodeFrom && nodeTo)
        {
            nodeAccountRemoveEdgeWithOtherNode(nodeFrom, nodeTo);
        }
        else
        {
            printf("The nodes you provided do not exist\n");
        }
    }
    else if (strcmp(command->command, "m") == 0 || strcmp(command->command, "modify") == 0)
    {
        char* nodeFromName = command->params[0];
        char* nodeToName = command->params[1];

        int oldSum = atoi(command->params[2]);
        int newSum = atoi(command->params[3]);

        char* oldDate = command->params[4];
        char* newDate = command->params[5];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        if(!nodeFrom)
        {
            printf("Non-existing node: %s\n", nodeFromName);
            return;
        }
        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);
        if(!nodeTo)
        {
            printf("Non-existing node: %s\n", nodeToName);
            return;
        }

        int result = nodeAccountFindAndModifyEdgeWithNode(nodeFrom,nodeTo, oldSum, newSum, oldDate, newDate);
        if(result == 0)
        {
            printf("Non-existing edge: %s %s %d %s\n", nodeFromName, nodeToName, oldSum, oldDate);
        }  
    }
    else if(strcmp(command->command, "f") == 0 || strcmp(command->command, "find") == 0)
    {
        char* nodeNameToLook = command->params[0];
        NodeAccount* nodeToLook = graphFindNode(graph, nodeNameToLook);
        if(nodeToLook)
        {
            nodeAccountPrintOutEdges(nodeToLook);
        }
        else
        {
            printf("Non-existing node: %s\n", nodeNameToLook);
        }
    }
    else if(strcmp(command->command, "r") == 0 || strcmp(command->command, "receiving") == 0)
    {
        char* nodeNameToLook = command->params[0];
        NodeAccount* nodeToLook = graphFindNode(graph, nodeNameToLook);
        if(nodeToLook)
        {
            nodeAccountPrintInEdges(nodeToLook);
        }
        else
        {
            printf("Non-existing node: %s\n", nodeNameToLook);
        }       
    }
    else if(strcmp(command->command, "c") == 0 || strcmp(command->command, "circleFind") == 0)
    {
        char* nodeName = command->params[0];
        NodeAccount* nodeToLook = graphFindNode(graph, nodeName);
        if(nodeToLook)
        {
            graphFindCircle(graph, nodeToLook, -1);
        }
        else
        {
            printf("Non-existing node: %s\n", nodeName);
        }
    }
    else if(strcmp(command->command, "fi") == 0 || strcmp(command->command, "findcircles") == 0)
    {
        char* nodeName = command->params[0];
        int minAmount = atoi(command->params[1]);
        NodeAccount* nodeToLook = graphFindNode(graph, nodeName);
        if(nodeToLook)
        {
            graphFindCircle(graph, nodeToLook, minAmount);
        }
        else
        {
            printf("Non-existing node: %s\n", nodeName);
        }
    }
    else if(strcmp(command->command, "t") == 0 || strcmp(command->command, "traceflow") == 0)
    {
        char* nodeName = command->params[0];
        int length = atoi(command->params[1]);
        NodeAccount* nodeToLook = graphFindNode(graph, nodeName);
        if(!nodeToLook)
        {
            printf("Non-existing node: %s\n", nodeName);
        }

        graphFindTraceflow(graph, nodeToLook, length);
    }
    else if(strcmp(command->command, "o") == 0 || strcmp(command->command, "connected") == 0)
    {
        char* nodeFromName = command->params[0];
        char* nodeToName = command->params[1];

        NodeAccount* nodeFrom = graphFindNode(graph, nodeFromName);
        if(!nodeFrom)
        {
            printf("Non-existing node: %s", nodeFromName);
            return;
        }
        
        NodeAccount* nodeTo  = graphFindNode(graph, nodeToName);
        if(!nodeTo)
        {
            printf("Non-existing node: %s", nodeToName);
            return;
        }

        if(nodeFrom && nodeTo)
        {
            graphFindPath(graph, nodeFrom, nodeTo);
        }
        else
        {
            printf("You didnt provide valid node names");
        }
    }
    else if(strcmp(command->command, "p") == 0 || strcmp(command->command, "print") == 0)
    {
        graphPrint(graph);
    }
    else
    {
        printf("Unrecognized command\n");
    }
}