/*
Student Name: Bryan Johnson
Student NetID: btj117
Date: 11/14/2020
Compiler Used: Clion using mingw
Program Description:
This program will execute commands or load a text file and will tokenize it in order to find commands. If the program
finds a command it attempts to execute the given command. The given commands associated with this program will be used
to create and implement a preemptive scheduling queue. This program will schedule tasks, add scheduled tasks to a
priority queue, and increment through both the priority queue and schedule via time steps.
*/

#ifndef HEAP_COMMANDS_H
#define HEAP_COMMANDS_H
class Process;
class Heap;
#include "Tokenizer.h"
#include "Process.h"
// function for processing text to parse and execute commands
// step function to be used in commands file

bool processText(istream &is, bool interactive = true);
void step_func();





#endif
