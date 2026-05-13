
#ifndef HEAP_H
#define HEAP_H
#include "Process.h"
#include <vector>
#include <iostream>
#include <iomanip>
// heap class and leading process class
class Process;
class Heap
{
private:
    std::vector<Process> heap;
    int size;
    int elements;

    void bubbleUp(int index);  //bubble up function
    void bubbleDown(int index);  //bubble down function
    void swap(int index1, int index2);  //swap function for heap sorting
    void insert(Process value);   //insert into heap function
    void removeVal(std::vector<Process>& value);   //remove root from heap and return it
    void display_heap(std::ostream& os);    //display contents of the heap
public:
    //public functions and constructor
    Heap(): heap(20), size(20), elements(0) {}
    void add(Process value);
    void remove(std::vector<Process>& value);
    void buildHeap(std::vector<Process> pile, int size);  //build heap based on given pile
    void display(std::ostream& os);
    bool peek(Process& value);
};

#endif //HEAP_HEAP_H
