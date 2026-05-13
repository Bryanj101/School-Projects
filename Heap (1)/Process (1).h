
#ifndef HEAP_PROCESS_H
#define HEAP_PROCESS_H

#include <vector>
#include <string>

class Process
{
public:
    std::string name;
    int priority;
    int arrives;
    int length;
    int elapsed_time;

    friend std::ostream& operator<< (std::ostream& os, Process& right);
    friend std::ostream& operator<< (std::ostream& os, std::vector<Process>& right);
};

std::vector<Process>  sched;

std::ostream &operator<<(std::ostream &os, Process& right)
{
    return os;
}

std::ostream &operator<<(std::ostream &os, std::vector<Process> &right) {
    return os;
}

void Schedule(Process value)
{
    sched.push_back({value});
}

#endif //HEAP_PROCESS_H
