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

//functions for process class
#include "Process.h"
bool compareArrival(const Process& lhs, const Process& rhs)
{
    return lhs.arrives < rhs.arrives;
}

std::ostream &operator<<(std::ostream &os, Process& right)
{
    return os;
}
//add new tasks to process schedule
void Process::schedule(std::vector<Process>& v,std::string name, int prio, int length, int arrives)
{
    Process task;
    task.name = name;
    task.priority = prio;
    task.length = length;
    task.arrives = arrives;
    v.push_back(task);
    std::sort(v.begin(), v.end(), compareArrival);
}



void Process::display_schedule(std::ostream& os, std::vector<Process> v)
{

    os << "Tasks yet to be scheduled..." << '\n';
    if (v.empty())
        os << "None" << '\n';
    for (int i = 0; i < v.size(); i++) {
        os << "\t" << v.at(i).name;
        os << " @" << v.at(i).priority;
        os << " for " << v.at(i).elapsed_time;
        os << " out of " << v.at(i).length;
        os << " arriving at " << v.at(i).arrives << '\n';
    }
}



bool operator<(const Process &a, const Process &b) {
    return a.priority < b.priority;
}

