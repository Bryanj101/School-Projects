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

// heap class
#include "Heap.h"

//heapify bubble up
void Heap::bubbleUp(int index)
{
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (heap[index].priority < heap[parent].priority)
    {
        swap(index, parent);
        bubbleUp(parent);
    }

}
//heapify bubble down
void Heap::bubbleDown(int index)
{
    int min = index;
    int left = 2 * index + 1;
    int right = left + 1;
    if (left > elements - 1) return;
    if (right > elements - 1) { min = left;}
    else {
        min = (heap[left].priority < heap[right].priority) ?
              left : right;
    }
    min = (heap[index].priority < heap[min].priority) ? index :
          min;
    if (min != index) {
        swap(index, min);
        bubbleDown(min);
    }
}
//swap function for sorting heap
void Heap::swap(int index1, int index2)
{
    Process tmp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = tmp;
}
// insert into the heap
void Heap::insert(Process value)
{
    heap[elements] = value;
    bubbleUp(elements);
    elements++;

}
// remove root and return the value
void Heap::removeVal(std::vector<Process>& value)
{
    if (elements != 0) {
        elements--;
        value.push_back(heap.at(0));
        heap[0] = heap[elements];
        bubbleDown(0);
        heap.erase(heap.begin());
    }
}
//displays content of heap
void Heap::display_heap(std::ostream& os)
{

    for (int i = 0; i < elements; i++)
    {
        os << heap[i].name;
        os << std::setw(4) << heap[i].priority;
        os << std::setw(4) << heap[i].length;
        os << std::setw(4) << heap[i].arrives;
        if (i < elements - 1)
        {
            os << '\n';
        }
    }
    os << '\n';

}
//calls private insert function
void Heap::add(Process value)
{
    insert(value);
}
//calls private insert function
void Heap::remove(std::vector<Process>& value)
{
    removeVal(value);
}
//calls private insert function
void Heap::buildHeap(std::vector<Process> pile, int size)
{
    std::copy(pile.begin(), pile.end(), heap.begin());
    elements = size;
    for (int index = (elements/2); index >= 0; index--)
        bubbleDown(index);

}
//calls private display function
void Heap::display(std::ostream& os)
{
    display_heap(os);
}
//peek function for root return
bool Heap::peek(Process& value)
{
    if (elements != 0) {
        value = heap[0];
        return true;
    }
    else
        return false;
}




