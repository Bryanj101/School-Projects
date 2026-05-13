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
#ifndef PROCESS_H
#define PROCESS_H
class Heap;

#include "Heap.h"
#include "Commands.h"
#include <vector>
#include <iostream>
#include <algorithm>

//process class mostly used for process attributes and some functions
class Process
{
public:
    //attributes
    std::string name;
    int priority;
    int length;
    int arrives;
    int elapsed_time;
    // constructors and functions
    Process(): name(), priority(0), length(0), arrives(0), elapsed_time(0){}
    Process(std::string name, int priority, int length, int arrives) :
    name(name), priority(priority), length(length), arrives(arrives), elapsed_time(0) {}
    static void schedule(std::vector<Process>& v, std::string name, int prio, int length, int arrives);  //add to vector
    static void display_schedule(std::ostream& os, std::vector<Process> v);   //display function for process vectors
    friend std::ostream& operator<< (std::ostream& os, Process& right);
};


#endif
