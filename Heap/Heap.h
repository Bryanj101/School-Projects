
#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <iostream>
#include <vector>
#include "Process.h"

class Heap
{
private:
    int* heap;
    int size;
    int elements;

    void bubbleUp(int index)
    {
        if (index == 0)
            return;
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent])
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
            min = (heap[left] < heap[right]) ?
                  left : right;
        }
        min = (heap[index] < heap[min]) ? index :
              min;
        if (min != index) {
            swap(index, min);
            bubbleDown(min);
        }
    }

    void swap(int index1, int index2)
    {
        int tmp = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = tmp;
    }

    void reallocate()
    {
        int* old = heap;
        size *= 2;
        heap = new int[size];
        for (int i = 0; i < elements; i++)
        {
            heap[i] = old[i];
        }
        delete[] old;
    }

    void insert(int value)
    {
        heap[elements] = {value};
        bubbleUp(elements);
        elements++;
    }

    bool removeVal(int& value)
    {
        elements--;
        value = heap[0];
        heap[0] = heap[elements];
        bubbleDown(0);
        return value;
    }
    void display_heap(std::ostream& os)
    {
        for (int i = 0; i < elements; i++)
        {
            os << heap[i];
            if (i < elements - 1)
            {
                os << ", ";
            }
        }
        os << '\n';
    }
public:
    Heap(): heap(new int[20]), size(20), elements(0) {}
    ~Heap();
    void add(int value)
    {
        insert(value);
    }
    void remove()
    {
        int value;
        removeVal(value);
    }
    void buildHeap(int *pile, int size)
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
};

Heap::~Heap()
{
    heap = nullptr;
    delete[] heap;
}


#endif //HEAP_HEAP_H
