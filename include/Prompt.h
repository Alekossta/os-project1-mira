#pragma once

typedef struct Command
{
    char* command;
    char** params;
    int param_count;
} Command;

void printCommand(char* commandName, char* commandDescription, char* commandSyntax);
void showPrompt();
Command readCommand();
void freeCommand(Command command);