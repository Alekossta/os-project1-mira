#include "CommandHandler.h"

void handleCommand(Graph* graph, Command* command)
{
    if(command->command == 'i')
    {
        for(unsigned i = 0; i < command->param_count; i++)
        {
            Node* createdNode = nodeCreate(command->params[i]);
            graphAddNode(graph, createdNode);
        }
    }
    else if(command->command == 'p')
    {
        graphPrint(graph);
    }
}