#include "../include/Prompt.h"
#include "stdio.h"
#include "Graph.h"
#include "CommandHandler.h"

#define NODE_MAX 1000

int main()
{
    Graph graph = graphCreate(NODE_MAX);
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