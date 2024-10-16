#include "CommandHandler.h"

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
        char* nodeFrom = command->params[1];
        char* nodeTo = command->params[2];

        // second param of strtod() returns the character we stopped converting at. we dont really care so NULL
        double amount = strtod(command->params[3], NULL);

        char* date  = command->params[4];

        edgeTransactionCreate(amount, date, nodeFrom, nodeTo);
        
        // do rest
    }
    else if(command->command == 'p')
    {
        graphPrint(graph);
    }
}