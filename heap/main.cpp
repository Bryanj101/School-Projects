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

#include <iostream>
#include "Commands.h"


int main() {
    std::cout <<
              "COMMAND LIST\n"
              "---------------------------------------------------------------------------------\n"
              "exit ... exit the program\n"
              "load file ... loads a file containing supported commands\n"
              "simulate ... enters simulation mode to allow for simulation commands\n"
              "schedule ... enters scheduling mode to allow for scheduling commands\n"
              "register <name> <priority> <length> <arrival> (schedule mode) ... registers tasks to the scheduling queue\n"
              "display ... depending on mode displays either the schedule or both the schedule and priority queue\n"
              "clear (schedule mode) ... clear command for scheduling mode to clear schedule\n"
              "remove <task> (schedule mode) ... removes scheduled task based on name of task\n"
              "step or step <number> (simulation mode) ... increases the time elapsed by an increment of 1 or more if "
              "integer given\n"
              "reset (simulation mode) ... clears priority queue and resets original scheduling\n"
              "run (simulation mode)... increments time steps until the end of the priority queue\n"
              "run til <number> (simulation mode) ... increments time steps until specified time\n"
              "---------------------------------------------------------------------------------\n";
    processText(std::cin);
    return 0;
}
