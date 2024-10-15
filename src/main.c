#include "../include/prompt.h"
#include "stdio.h"
#include "Node.h"
#include "Graph.h"
#include "CommandHandler.h"
int main()
{
    Graph graph = graphCreate();
    Command command;
    do
    {
        showPrompt();
        command = readCommand();
        handleCommand(&graph, &command);
        freeCommand(command);
    } while (command.command != 'e');

    return 0;
}