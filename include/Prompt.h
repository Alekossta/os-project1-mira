#pragma once

// struct that stores command information
// command = the command the user chose (first word)
// params = array of params
// param_count = counter for array of params
typedef struct Command
{
    char* command;
    char** params;
    int param_count;
} Command;

// prints format of command
void printCommand(char* commandName, char* commandDescription, char* commandSyntax);

// shows prompt
void showPrompt();

// reads command
Command readCommand();

// frees command
void freeCommand(Command command);