#include "../include/Prompt.h"
#include "stdio.h"
#include <string.h>
#include "BytesCounter.h"

void printCommand(char* commandName, char* commandDescription, char* commandSyntax)
{
    printf("--- Command: %s ---\n", commandName);
    printf("Description: %s\n", commandDescription);
    printf("Syntax: %s\n", commandSyntax);
};

void showPrompt()
{
    printCommand("i", "insert new n nodes", "i Ni Nj Nk");
    printCommand("n", "insert a new edge transaction from Ni to Nj nodes with date and sum (nodes can be new).",
    "n Ni Nj sum date");
    printCommand("d", "delete n nodes (edge transactions will also be deleted)", "d Ni Nj Nk");
    printCommand("l", "delete a random edge transaction between Ni and Nj", "l Ni Nj");
    printCommand("m", "modify the sum and date of an edge transaction. search by sum and data.",
    "m Ni Nj sum sum1 date date1");
    printCommand("f", "show all outgoing edge transactions of a node Ni", "f Ni");
    printCommand("r", "show all ingoing edge transactions of a node Ni", "r Ni");
    printCommand("c", "find if node Ni is in a simple circle and show that.", "c Ni");
    printCommand("fi", "find if node Ni is in a circular transaction. min sum every edge should have is k",
    "y Ni k");
    printCommand("t", "find all transaction flows starting from node Ni with path length m", "t Ni m");
    printCommand("o", "find if there is a path between Ni and Nj and print it", "o Ni Nj");
    printCommand("e", "exit the program and save. show bytes used", "e");
    printCommand("p", "print the nodes of the graph", "p");
};

Command readCommand()
{
    Command command;
    command.params = NULL;
    command.param_count = 0;

    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char* token = strtok(input, " ");
    if(token != NULL)
    {
        command.command = token;
    }
    else
    {
        printf("First token was null");
    }

    while(token != NULL)
    {   
        token = strtok(NULL, " ");
        if(token)
        {
            command.params = realloc(command.params, sizeof(char*) * (command.param_count + 1));
            bytesCounter += sizeof(char*);

            command.params[command.param_count] = malloc(strlen(token) + 1); // \0
            bytesCounter += strlen(token) + 1;

            strcpy(command.params[command.param_count], token);

            command.param_count++;
        }
    }

    return command;
}

void freeCommand(Command command)
{
    for(int i = 0; i < command.param_count; i++) {
        bytesCounter -= (strlen(command.params[i]) + 1); // \0
        free(command.params[i]);
    }
    bytesCounter -= sizeof(char*) * (command.param_count);
    free(command.params);
}