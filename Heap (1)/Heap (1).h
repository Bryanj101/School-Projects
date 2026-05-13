
#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include "Process.h"

class Heap
{
private:
    Process* heap;
    int size;
    int elements;

    void bubbleUp(int index)
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
    void bubbleDown(int index)
    {
        int min = index;
        int left = 2 * index + 1;
        int right = left + 1;
        if (left > elements - 1) return;
        if (right > elements - 1) { min = left; }
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

    void swap(int index1, int index2)
    {
        Process tmp = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = tmp;
    }

    void reallocate()
    {
        Process* old = heap;
        size *= 2;
        heap = new Process[size];
        for (int i = 0; i < elements; i++)
        {
            heap[i] = old[i];
        }
        delete[] old;
    }

    void insert(Process value)
    {
        heap[elements] = value;
        bubbleUp(elements);
        elements++;
        sched.erase(sched.begin());
    }

    Process removeVal(Process& value)
    {
        elements--;
        value = heap[0];
        heap[0] = heap[elements];
        bubbleDown(0);
        return value;
    }
    void display_heap(std::ostream& os)
    {

        for (int i = 0; i < elements; i++) {
            os << heap[i].name << '\t';
            os << heap[i].priority << '\t';
            os << heap[i].arrives << '\t';
            os << heap[i].length << '\t';
            os << heap[i].elapsed_time << '\t';
            if (i < elements - 1) {
                os << '\n';
            }
        }
        os << '\n';

    }
public:
    Heap(): heap(new Process[20]), size(20), elements(0) {}
    void add(Process value)
    {
        insert(value);
    }
    Process remove(Process& value)
    {
        removeVal(value);
        return value;
    }
    void buildHeap(Process* pile, int size)
    {
        heap = pile;
        elements = size;
        for (int index = (elements/2); index >= 0; index--)
            bubbleDown(index);

    }
    void display(std::ostream& os)
    {
        display_heap(os);
    }
    void peek()
    {

    }
};


#endif //HEAP_HEAP_H
