#include "../include/Prompt.h"
#include "stdio.h"
#include "Graph.h"
#include "CommandHandler.h"

#define NODE_MAX 19000

int main(int argumentCount, char* arguments[])
{
    Graph graph = graphCreate(NODE_MAX);

    // read file
    FILE* inputFile = fopen(arguments[2], "r");

    if(inputFile)
    {
        printf("read\n");
        char nodeFrom[100];
        char nodeTo[100];
        char sum[100];
        char date[100];

        printf("read2\n");

        while (fscanf(inputFile, "%99s %99s %99s %99s", nodeFrom, nodeTo, sum, date) == 4) {
            printf("read3\n");
            // make a command
            Command command;
            command.command = 'n';
            command.param_count = 4;
            command.params = malloc(sizeof(char*) * 4);
            command.params[0] = nodeFrom;
            command.params[1] = nodeTo;
            command.params[2] = sum;
            command.params[3] = date;
            printf("h\n");
            handleCommand(&graph,&command);
            // we dont have to free command here because strings here are on static memory
        }
    }
    else
    {
        printf("Could not open input file\n");
    }

    fclose(inputFile);

    // command prompt loop
    Command command;
    do
    {
        showPrompt();
        command = readCommand();
        handleCommand(&graph, &command);
        freeCommand(command);
    } while (command.command != 'e');

    // write file


    return 0;
}