#include "../include/Prompt.h"
#include "stdio.h"
#include "Graph.h"
#include "CommandHandler.h"
#include "BytesCounter.h"

#define NODE_MAX 19000

int main(int argumentCount, char* arguments[])
{
    Graph graph = graphCreate(NODE_MAX);

    char* inputFileName = NULL;
    char* outputFileName = NULL;

    for (int i = 1; i < argumentCount; i++) {
        if (strcmp(arguments[i], "-i") == 0) {
            if (i + 1 < argumentCount) {
                inputFileName = arguments[i + 1];
                i++;
            } else {
                printf("Error: Missing value for -i option\n");
                return 1;
            }
        } else if (strcmp(arguments[i], "-o") == 0) {
            if (i + 1 < argumentCount) {
                outputFileName = arguments[i + 1];
                i++;
            } else {
                printf("Error: Missing value for -o option\n");
                return 1;
            }
        } else {
            printf("Unknown argument: %s\n", arguments[i]);
        }
    }

    // read file
    FILE* inputFile = fopen(arguments[2], "r");

    if(inputFile)
    {
        char nodeFrom[100];
        char nodeTo[100];
        char sum[100];
        char date[100];

        while (fscanf(inputFile, "%99s %99s %99s %99s", nodeFrom, nodeTo, sum, date) == 4) {
            Command command;
            command.command = "n";
            command.param_count = 4;
            command.params = malloc(sizeof(char*) * 4);
            command.params[0] = nodeFrom;
            command.params[1] = nodeTo;
            command.params[2] = sum;
            command.params[3] = date;
            handleCommand(&graph,&command);
            free(command.params);
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
    } while (strcmp(command.command, "e") != 0 && strcmp(command.command, "exit") != 0);

    // write file

    // we will iterate through all nodes
    // and get all the outgoing edge transactions
    // and write all transactions like the input files
    
    FILE* outputFile = fopen(outputFileName, "w");
    if(outputFile)
    {
        graphWriteToFile(&graph, outputFile);
    }
    else
    {
        printf("Error opening output file\n");
    }

    fclose(outputFile);

    graphFree(&graph);

    printf("Bytes used: %zu\n", bytesCounter);
    
    return 0;
}